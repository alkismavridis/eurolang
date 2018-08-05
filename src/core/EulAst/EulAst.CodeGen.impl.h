#pragma once

//region VAR DECLARATION
/**
    returns the type declared type, if any.
    The type that can be extracted from the value otherwise.
    TODO what happens if neither type not value is provided?
*/
llvm::Type* VarDeclaration::generateType(EulCodeGenContext* ctx) {
    //1. If no type is declared, get one from the value.
    return llvm::IntegerType::get(ctx->context, 32);


    //TODO what a mess!


    //if (this->type == nullptr) return this->value->generateType(ctx);

    //2. If the type is LateDeclared, try to get it.
    //if(this->type->isLateDeclared() && this->llvmType==nullptr) return ctx->createEulType
}
//endregion



//region STATEMENTS
void EulStatement::generateStatement(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulStatement::generateStatement was called.");
    //return nullptr; //TODO
}

void VarDeclarationStatement::generateStatement(EulCodeGenContext* ctx) {
    for (auto decl : *this->declarations) {
        auto const varName = decl->id->name;

        //1. Check if variable already exists ON the current scope. Throw an error if so
        auto const symbol = ctx->currentScope->get(varName);
        if (symbol == nullptr) ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, varName + " not found."));

        //2. Declare the variable, and add it to the scope.
        llvm::AllocaInst* allocInst = ctx->builder.CreateAlloca(
            llvm::IntegerType::get(ctx->context, 32),  //TODO get the proper type: the type of that variable
            nullptr,
            varName
        );


        //3. If the value has an assignment, evaluate it.
        if (decl->value != nullptr) ctx->builder.CreateStore(decl->value->generateValue(ctx), allocInst);

        //4. Add the llvm value to the symbol
        symbol->allocInstruction = allocInst;
    }
}

void EulExpStatement::generateStatement(EulCodeGenContext* ctx) {
    std::cout << "EulExpStatement" << std::endl;
    //return nullptr; //TODO
}

void ReturnStatement::generateStatement(EulCodeGenContext* ctx) {
    //TODO check if return statement matches function return type.


    ctx->builder.CreateRet(
        this->exp == nullptr? nullptr : this->exp->generateValue(ctx)
    );
}
//endregion




//region EXPRESSIONS
llvm::Value* EulArrayAccessExp::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulArrayAccessExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulFunctionCallExp::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulFunctionCallExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulInfixExp::generateValue(EulCodeGenContext* ctx) {
    //1. Calculate the two operands
    llvm::Value* leftValue = this->left->generateValue(ctx);
    llvm::Value* rightValue = this->right->generateValue(ctx);
    if (!leftValue || !rightValue) return nullptr;

    //2. Return the operation
    return this->oper->performInfix(leftValue, rightValue, ctx);
}

llvm::Value* EulPrefixExp::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulPrefixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulSuffixExp::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulSuffixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulTokenExp::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulTokenExp" << std::endl;
    return nullptr; //TODO what this even means?
}
//endregion