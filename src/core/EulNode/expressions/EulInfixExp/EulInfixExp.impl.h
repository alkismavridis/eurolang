#pragma once


//region LIFE CYCLE
EulInfixExp::EulInfixExp(std::shared_ptr<ValueNode> left, EulOperator* oper, std::shared_ptr<ValueNode> right) {
    this->left = left;
    this->oper = oper;
    this->right = right;
}
//endregion



//region CORE FUNCTIONS
EulExpressionType EulInfixExp::getExpressionType() { return EulExpressionType::INFIX_EXP; }
//endregion



//region CODE GENERATION
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
        &this->compileTimeType,
        ctx
    );
}

llvm::Value* EulInfixExp::generateAssignment(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Get the id token out of the left operand
    if (!this->left->isSymbolId())
        throw new EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Cannot assign a value to a non id token.");
    EulSymbolNameNode* asId = static_cast<EulSymbolNameNode*>(this->left.get());

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
//endregion



//region SERIALIZING
void EulInfixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulInfixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"left\":";
    this->left->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"right\":";
    this->right->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
