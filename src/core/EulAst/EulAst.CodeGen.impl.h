#pragma once

//region VAR DECLARATION
/**
    returns the type declared type, if any.
    The type that can be extracted from the value otherwise.
*/
std::shared_ptr<EulType> VarDeclaration::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    //1. If there is a declared type, return that
    if (this->varType != nullptr) return this->varType;

    //2. If there is no return type, but there is a value, return the "default" type for that value
    if (this->value != nullptr) return this->value->getEulType(ctx, 0);

    //3. TODO what happens if neither type not value is provided?
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT IMPLEMENTED: variable without initial value.");

}
//endregion



//region STATEMENTS
void EulStatement::generateStatement(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulStatement::generateStatement was called.");
}

void EulStatement::assertStatementReachable(EulCodeGenContext* ctx) {
    if (ctx->builder.GetInsertBlock()->getTerminator() == nullptr) return;
    throw EulError(EulErrorType::SEMANTIC, "Unreachable statement.");
}


void VarDeclarationStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    for (auto decl : *this->declarations) {
        auto const varName = decl->id->name;

        //1. Get the variable. Throw an error if it does not exists
        auto const symbol = ctx->currentScope->get(varName);
        if (symbol == nullptr) {
            ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, varName + " not found."));
            return;
        }

        //2. Store the value.
        //2a. Get the runtime value
        llvm::Value* runtimeValue;
        if (decl->value==nullptr) {
            //undefined value. Let llvm optimize what will happen
            runtimeValue = llvm::UndefValue::get(decl->varType->getLlvmType(ctx));
        }
        else {
            //we have a value. Lets compute it and store it.
            runtimeValue = decl->value->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
        }

        //2b. Set the symbol type
        symbol->varType = decl->getEulType(ctx, 0);

        //2b. cast the value to the declared type (or the type that the expression indicated, if no explicit type was specified)
        auto castedValue = decl->value==nullptr?
            runtimeValue:
            symbol->varType->castValue(runtimeValue, symbol->varType.get(), false, ctx);

        //2c. create the allocation and the store instruction
        auto allocInst = ctx->builder.CreateAlloca(symbol->varType->getLlvmType(ctx), nullptr, varName);
        ctx->builder.CreateStore(castedValue, allocInst);
        symbol->llvmValue = allocInst;
    }
}

void EulExpStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);
    exp->generateValue(ctx, EulCodeGenFlags_NONE);
}

void ReturnStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    //1. Get return value
    auto retValue = this->exp == nullptr?
        nullptr :
        this->exp->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);


    //2. Cast to return type
    auto retType = ctx->compiler->program.nativeTypes.int32Type.get(); //TODO when we implement functions, the actual return type will go here.
    auto castedValue = retType->castValue(
        retValue,
        this->exp->getEulType(ctx, 0).get(),
        false,
        ctx
    );

    //3. Return the value
    ctx->builder.CreateRet(castedValue);
}


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
    for (auto instr : *expBlock->block->statements) instr->generateStatement(ctx);
    ctx->builder.CreateBr(endBlock);
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
        for (auto instr : *this->elseSection->statements) instr->generateStatement(ctx);
        ctx->builder.CreateBr(endIfBlock);
    }

    //4. Restore scope and inserting block
    ctx->currentScope = ctx->currentScope->superScope;
    ctx->builder.SetInsertPoint(endIfBlock);
}
//endregion




//region EXPRESSIONS
llvm::Value* EulArrayAccessExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulArrayAccessExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulFunctionCallExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Get the function, and set the result type of the expression
   auto functionToCall = this->func->generateValue(ctx, EulCodeGenFlags_NONE);
   auto funcType = static_cast<EulFunctionType*>(this->func->getEulType(ctx, 0).get());
   this->compileTimeType = funcType->retType;


   //2. Check that parameter count matches
   auto paramsSize = (this->params == nullptr)? 0 : this->params->size();
   if (funcType->argTypes.size() != paramsSize)
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED wrong parameter list count.");

   //3. Get the args
   std::vector<llvm::Value*> args;
   for (int i=0, len = paramsSize; i<len; ++i) {
        auto argType = funcType->argTypes[i];
        auto param = (*this->params)[i];

        auto castedArgument = argType->castValue(
           param->generateValue(ctx, EulCodeGenFlags_LOAD_VAR),
           param->getEulType(ctx,0).get(),
           false,
           ctx
        );
       args.push_back(castedArgument);
   }

   return ctx->builder.CreateCall(functionToCall, llvm::ArrayRef<llvm::Value*>(args));
}

llvm::Value* EulInfixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    if (this->oper->isAssignment()) return this->generateAssignment(ctx, flags);

    //1. Calculate the values of the two operands. This will generate their types, too
    llvm::Value* leftValue = this->left->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    llvm::Value* rightValue = this->right->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    if (!leftValue || !rightValue) return nullptr;

    //2. Perform and return the operation
    return this->oper->performInfix(
        leftValue,
        this->left->getEulType(ctx, 0),
        rightValue,
        this->right->getEulType(ctx, 0),
        &this->compileTimeType, ctx
    );
}

llvm::Value* EulInfixExp::generateAssignment(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Get the id token out of the left operand
    if (this->left->getType() != EulTokenType::ID)
        throw new EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Cannot assign a value to a non id token.");
    EulIdToken* asId = static_cast<EulIdToken*>(this->left.get());

    //2. Get the symbol, and assert that it is mutable.
    auto symbol = ctx->currentScope->get(asId->name);
    if (symbol==nullptr)
        throw new EulError(EulErrorType::SEMANTIC, (asId->name) + " is not defined.");
    if (symbol->changeType != yy::EulParser::token::VAR)
        throw new EulError(EulErrorType::SEMANTIC, "Symbol " + (asId->name) + " is immutable. Reassigning a value to it is forbidden.");

    //3. Calculate the right operand
    llvm::Value* rightValue = this->right->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);

    //4. Make the assignment
    return this->oper->assignInfix(
        symbol.get(),
        rightValue,
        this->right->getEulType(ctx, 0),
        &this->compileTimeType, ctx
    );
}

llvm::Value* EulPrefixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulPrefixExp::generateValue" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulSuffixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulSuffixExp::generateValue" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulTokenExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulTokenExp::generateValue" << std::endl;
    return nullptr; //TODO what this even means?
}
//endregion