#pragma once

//region VAR DECLARATION
/**
    returns the type declared type, if any.
    The type that can be extracted from the value otherwise.
*/
llvm::Type* VarDeclaration::generateType(EulCodeGenContext* ctx) {
    //1. If there is a declared type, return that
    auto declaredType = this->varType == nullptr?
        nullptr :
        this->varType->getLlvmType(ctx);

    if (declaredType != nullptr) return declaredType;

    //2. If there is no return type, but there is a value, return the "default" type for that value
    if (this->value != nullptr) return this->value->generateType(ctx);

    //3. TODO what happens if neither type not value is provided?
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT IMPLEMENTED: variable without initial value.");

}
//endregion



//region STATEMENTS
void EulStatement::generateStatement(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulStatement::generateStatement was called.");
}

void VarDeclarationStatement::generateStatement(EulCodeGenContext* ctx) {
    for (auto decl : *this->declarations) {
        auto const varName = decl->id->name;

        //1. Get the variable. Throw an error if it does not exists
        auto const symbol = ctx->currentScope->get(varName);
        if (symbol == nullptr) ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, varName + " not found."));

        //2. Declare the variable, and add it to the scope.
        auto declType = decl->generateType(ctx);
        llvm::AllocaInst* allocInst = ctx->builder.CreateAlloca(
            declType,
            nullptr,
            varName
        );

        //3. If the value has an assignment, evaluate it.
        if (decl->value != nullptr) {
            auto runtimeValue = decl->value->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
            auto castedValue = ctx->castValue(runtimeValue, declType);
            ctx->builder.CreateStore(castedValue, allocInst);
        }
        else ctx->compiler->addError(EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED " + varName + " does not have a init value"));

        //4. Add the llvm value to the symbol
        symbol->llvmValue = allocInst;
    }
}

void EulExpStatement::generateStatement(EulCodeGenContext* ctx) {
    exp->generateValue(ctx, EulCodeGenFlags_NONE);
}

void ReturnStatement::generateStatement(EulCodeGenContext* ctx) {
    //1. Get return value
    auto retValue = this->exp == nullptr?
        nullptr :
        this->exp->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);


    //2. Cast to return type
    auto castedValue = ctx->castValue(
        retValue,
        ctx->builder.getCurrentFunctionReturnType()
    );

    //3. Return the value
    ctx->builder.CreateRet(castedValue);
}
//endregion




//region EXPRESSIONS
llvm::Value* EulArrayAccessExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulArrayAccessExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulFunctionCallExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Get the function
    auto functionToCall = this->func->generateValue(ctx, EulCodeGenFlags_NONE);

    //2. Get the args
    std::vector<llvm::Value*> args;
    for (auto const& param: *this->params) {
        args.push_back(param->generateValue(ctx, EulCodeGenFlags_LOAD_VAR));
    }

    return ctx->builder.CreateCall(functionToCall, llvm::ArrayRef<llvm::Value*>(args));
}

llvm::Value* EulInfixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Calculate the two operands
    llvm::Value* leftValue = this->left->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    llvm::Value* rightValue = this->right->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    if (!leftValue || !rightValue) return nullptr;

    //2. Return the operation
    return this->oper->performInfix(leftValue, rightValue, ctx);
}

llvm::Value* EulPrefixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulPrefixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulSuffixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulSuffixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulTokenExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulTokenExp" << std::endl;
    return nullptr; //TODO what this even means?
}
//endregion