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
        if (symbol == nullptr) ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, varName + " not found."));

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
        auto declLlvmType = symbol->varType->getLlvmType(ctx);
        auto castedValue = decl->value==nullptr?
            runtimeValue:
            ctx->castValue(runtimeValue, declLlvmType, symbol->varType.get());

        //2c. create the allocation and the store instruction
        auto allocInst = ctx->builder.CreateAlloca(declLlvmType, nullptr, varName);
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
    auto castedValue = ctx->castValue(
        retValue,
        ctx->builder.getCurrentFunctionReturnType(),
        ctx->compiler->program.nativeTypes.int32Type.get() //TODO when we implement functions, the actual return type will go here.
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
        auto castedArgument = ctx->castValue(
           (*this->params)[i]->generateValue(ctx, EulCodeGenFlags_LOAD_VAR),
           argType->getLlvmType(ctx),
           argType.get()
        );
       args.push_back(castedArgument);
   }

   return ctx->builder.CreateCall(functionToCall, llvm::ArrayRef<llvm::Value*>(args));
}

llvm::Value* EulInfixExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. Calculate the two operands
    llvm::Value* leftValue = this->left->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    llvm::Value* rightValue = this->right->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
    if (!leftValue || !rightValue) return nullptr;

    //2. Get the result type.
    auto leftEulType = this->left->getEulType(ctx, 0);
    auto rightEulType = this->right->getEulType(ctx, 0);
    this->compileTimeType = this->oper->getInfixResultType(leftEulType, rightEulType, ctx);

    //3. Perform and return the operation
    return this->oper->performInfix(leftValue, rightValue, this->compileTimeType, ctx);
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






//region TYPES
llvm::Type* EulType::getLlvmType(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::getLlvmType was called.");
}

llvm::Type* EulIntegerType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}

llvm::Type* EulCharType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}

llvm::Type* EulFloatType::getLlvmType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 32: return llvm::Type::getFloatTy(ctx->context);
        case 64: return llvm::Type::getDoubleTy(ctx->context);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64.");
    }
}

llvm::Type* EulStringType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}

llvm::Type* EulNamedType::getLlvmType(EulCodeGenContext* ctx) {
    return ctx->module->getTypeByName(this->name);
}

llvm::Type* EulPointerType::getLlvmType(EulCodeGenContext* ctx) {
    auto type = this->contentType->getLlvmType(ctx);
    for (int i = this->depth; i--;) type = type->getPointerTo();
    return type;
}

llvm::Type* EulFunctionType::getLlvmType(EulCodeGenContext* ctx) {
    //1. Build argument list
    std::vector<llvm::Type*> llvmArgList;
    for (auto const& argType : this->argTypes) llvmArgList.push_back(argType->getLlvmType(ctx));

    auto ret = llvm::FunctionType::get(
        this->retType==nullptr? llvm::Type::getVoidTy(ctx->context) : this->retType->getLlvmType(ctx),
        llvm::ArrayRef<llvm::Type*>(llvmArgList),
        false
    );

    return ret;
}
//endregion