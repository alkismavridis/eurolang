#pragma once


//region LIFE CYCLE
ReturnStatement::ReturnStatement(std::shared_ptr<ValueNode> exp) {
    this->exp = exp;
}
//endregion


//region CORE FUNCTIONS
EulStatementType ReturnStatement::getStatementType() { return EulStatementType::RETURN_STATEMENT; }
//endregion


//region CODE GENERATION
void ReturnStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    //1. Get return value
    auto retValue = this->exp == nullptr?
        nullptr :
        this->exp->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);

    //2. Cast the expression type to the return type
    auto retType = ctx->currentFunction->functionType->retType.get();
    auto expressionType = this->exp==nullptr?
        ctx->compiler->program.nativeTypes.voidType.get() :
        this->exp->getEulType(ctx, 0).get();

    auto castedValue = retType->castValue(
        retValue,
        expressionType,
        false,
        ctx
    );

    //3. Return the value
    ctx->builder.CreateRet(castedValue);
}
//endregion


//region SERIALIZATION
void ReturnStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"ReturnStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\": ";
    if (this->exp == nullptr) out << "null" << std::endl;
    else {
        this->exp->toJson(out, tabs);
        std::cout << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
