#pragma once



//region LIFE CYCLE
EulFunctionCallExp::EulFunctionCallExp(std::shared_ptr<ValueNode> func, std::shared_ptr<std::vector<std::shared_ptr<ValueNode>>> params) {
    this->func = func;
    this->params = params;
}
//endregion



//region CORE FUNCTIONS
EulExpressionType EulFunctionCallExp::getExpressionType() { return EulExpressionType::FUNCTION_CALL; }
//endregion



//region CODE GENERATION
llvm::Value* EulFunctionCallExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Get the function, and set the result type of the expression
    auto functionToCall = this->func->generateValue(ctx, EulCodeGenFlags_NONE);
    auto funcType = static_cast<EulFunctionType*>(this->func->getEulType(ctx, 0).get());
    this->compileTimeType = funcType->retType;


    //2. Check that parameter count matches
    int actualParamCount = (this->params == nullptr)? 0 : this->params->size();
    int nonVarargParamCount = funcType->argTypes.size();
    if (!funcType->isParameterCountValid(actualParamCount))
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED wrong parameter list count.");

    //3. Get the args
    std::vector<llvm::Value*> args;
    for (int i=0; i<actualParamCount; ++i) {
        //the type may be in the regular area, or in the varArg area. In any case, get it.
        auto argType = i<nonVarargParamCount? funcType->argTypes[i] : funcType->varArgsType;
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
//endregion



//region SERIALIZATION
void EulFunctionCallExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunctionCallExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"func\":";
    this->func->toJson(out, tabs+1);
    out << std::endl;


    //print parameters
    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->params == nullptr) out << "\"params\": null" << std::endl;
    else {
        out << "\"params\": [" << std::endl;

        //print one parameter in each loop step
        for (auto p : *this->params) {
            for (int i=tabs+1; i>=0; --i) out << "\t";
            p->toJson(out, tabs+2);
            out << "," << std::endl; //TODO last entry should be without comma
        }
        for (int i=tabs; i>=0; --i) out << "\t";
        out << "]" << std::endl;
    }

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
