#pragma once


//region LIFE CYCLE
EulIfStatement::EulIfStatement(std::shared_ptr<ValueNode> condition, std::shared_ptr<EulCodeBlock> ifBlock) : ifSection(condition, ifBlock) {
    this->elseIfs = nullptr;
    this->elseSection = nullptr;
}

EulIfStatement::EulIfStatement(
    std::shared_ptr<ValueNode> condition,
    std::shared_ptr<EulCodeBlock> ifBlock,
    std::shared_ptr<EulCodeBlock> elseSection) :
    ifSection(condition, ifBlock) {
    this->elseIfs = nullptr;
    this->elseSection = elseSection;
}

EulIfStatement::EulIfStatement(
    std::shared_ptr<ValueNode> condition,
    std::shared_ptr<EulCodeBlock> ifBlock,
    std::shared_ptr<std::vector<std::shared_ptr<EulExpressionCodeBlock>>> elseIfs,
    std::shared_ptr<EulCodeBlock> elseSection) :
    ifSection(condition, ifBlock) {
    this->elseIfs = elseIfs;
    this->elseSection = elseSection;
}
//endregion



//region CORE FUNCTIONS
EulStatementType EulIfStatement::getStatementType() { return EulStatementType::IF_STATEMENT; }
//endregion



//region CODE GENERATION
/** The scope and the basic block for the CONDITION must be already set in ctx before this function is being called.  */
void EulIfStatement::generateConditionBlock(EulExpressionCodeBlock* expBlock, llvm::BasicBlock* blockOnFail, llvm::BasicBlock* endBlock, llvm::Function* currentFunction, EulCodeGenContext* ctx) {
    //1. Generate condition statement and cast the result into a boolean
    auto condition = expBlock->expression->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    condition = ctx->compiler->program.nativeTypes.booleanType->castValue(
        condition,
        expBlock->expression->getEulType(ctx, 0).get(),
        true,
        ctx
    );

    //3. Create the break instruction
    auto blockForStatements = llvm::BasicBlock::Create(ctx->context, "", currentFunction);
    ctx->builder.CreateCondBr(condition, blockForStatements, blockOnFail);

    //4. Jump into the if block and execute its statements
    ctx->currentScope = expBlock->block->scope;
    ctx->builder.SetInsertPoint(blockForStatements);
    expBlock->block->generateStatements(ctx);

    if (ctx->builder.GetInsertBlock()->getTerminator() == nullptr) {
        ctx->builder.CreateBr(endBlock);
    }
}


llvm::BasicBlock* EulIfStatement::getFailingIfBLock(llvm::Function* currentFunction, llvm::BasicBlock* endBlock, EulCodeGenContext* ctx) {
    //1. Attempt to return the first else if
    auto elseIfs = this->elseIfs;
    if (elseIfs!=nullptr && !elseIfs->empty()) return llvm::BasicBlock::Create(ctx->context, "", currentFunction);

    //2. Attempt to return the else block
    if (this->elseSection!=nullptr) return llvm::BasicBlock::Create(ctx->context, "", currentFunction);

    //3. Single if block. Return the endBlock
    return endBlock;
}

void EulIfStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    //1. Create the if section
    auto currentFunction = ctx->builder.GetInsertBlock()->getParent();
    auto endIfBlock = llvm::BasicBlock::Create(ctx->context, "", currentFunction);
    auto blockToJumpOnFailure = this->getFailingIfBLock(currentFunction, endIfBlock, ctx);
    this->generateConditionBlock(&this->ifSection, blockToJumpOnFailure, endIfBlock, currentFunction, ctx);

    //2. Generate else ifs, if any
    const int elseIfCount = this->elseIfs==nullptr? 0 : this->elseIfs->size();
    const bool hasElse = this->elseSection != nullptr;
    if (elseIfCount>0) {
        //2a. Prepare the block for the first elseif condition
        ctx->builder.SetInsertPoint(blockToJumpOnFailure);

        blockToJumpOnFailure = nullptr;
        for (int i = 0, len = this->elseIfs->size(); i<len; ++i) {
            //2b. Determine the block to jump if condition fails
            if (hasElse || i < elseIfCount-1) {
                blockToJumpOnFailure = llvm::BasicBlock::Create(ctx->context, "", currentFunction); //the next condition block
            }
            else blockToJumpOnFailure = endIfBlock;


            //2c. Prepare scope and entry point
            ctx->currentScope = ctx->currentScope->superScope;
            this->generateConditionBlock(this->elseIfs->at(i).get(), blockToJumpOnFailure, endIfBlock, currentFunction, ctx);

            //2d. Prepare the entry point for the next iteration (or the else block, or the end block)
            ctx->builder.SetInsertPoint(blockToJumpOnFailure);
        }
    }
    else if(hasElse) {
        //setup else
        ctx->builder.SetInsertPoint(blockToJumpOnFailure);
    }

    //3. Generate else section, if any
    if (hasElse) {
        //SetInsertPoint should be already called at this point...
        ctx->currentScope = this->elseSection->scope;
        this->elseSection->generateStatements(ctx);
        if (ctx->builder.GetInsertBlock()->getTerminator() == nullptr) ctx->builder.CreateBr(endIfBlock);
    }

    //4. Restore scope and inserting block
    ctx->currentScope = ctx->currentScope->superScope;
    ctx->builder.SetInsertPoint(endIfBlock);
}
//endregion



//region SERIALIZATION
void EulIfStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCodeBlock TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
