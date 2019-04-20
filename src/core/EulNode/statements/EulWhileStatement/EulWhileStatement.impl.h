#pragma once


//region LIFE CYCLE
EulWhileStatement::EulWhileStatement(std::shared_ptr<ValueNode> condition, std::shared_ptr<EulCodeBlock> ifBlock) : expBlock(condition, ifBlock) {
}
//endregion



//region CORE FUNCTIONS
EulStatementType EulWhileStatement::getStatementType() { return EulStatementType::WHILE_STATEMENT; }
//endregion



//region CODE GENERATION
void EulWhileStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    //1. Create the necessary blocks
    auto currentFunction = ctx->builder.GetInsertBlock()->getParent();
    auto conditionBlock = llvm::BasicBlock::Create(ctx->context, "", currentFunction);
    auto statementsBlock = llvm::BasicBlock::Create(ctx->context, "", currentFunction);
    auto endBlock = llvm::BasicBlock::Create(ctx->context, "", currentFunction);

    //2. Jump into the condition block
    ctx->builder.CreateBr(conditionBlock);
    ctx->builder.SetInsertPoint(conditionBlock);

    //3. Execute the condition
    auto condition = this->expBlock.expression->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    condition = ctx->compiler->program.nativeTypes.booleanType->castValue(
        condition,
        this->expBlock.expression->getEulType(ctx, 0).get(),
        true,
        ctx
    );
    ctx->builder.CreateCondBr(condition, statementsBlock, endBlock);

    //4. Execute the statements block
    ctx->currentScope = this->expBlock.block->scope;
    ctx->builder.SetInsertPoint(statementsBlock);
    this->expBlock.block->generateStatements(ctx);
    if (ctx->builder.GetInsertBlock()->getTerminator() == nullptr) {
        ctx->builder.CreateBr(conditionBlock);
    }

    //5. Restore scope and block for the next commands
    ctx->currentScope = ctx->currentScope->superScope;
    ctx->builder.SetInsertPoint(endBlock);
}
//endregion



//region SERIALIZATION
void EulWhileStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulWhileStatement TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
