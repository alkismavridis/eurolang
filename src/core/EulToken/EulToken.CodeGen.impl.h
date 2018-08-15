#pragma once

llvm::Value* EulToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateValue was called, but should not!");
}

llvm::Type* EulToken::generateType(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateType was called, but should not!");
}



//CHAR
llvm::Value* EulCharToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, false));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32");
    }
}

llvm::Type* EulCharToken::generateType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 8:
        case 16:
        case 32: return llvm::IntegerType::get(ctx->context, this->size);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32");
    }
}



//FLOAT
llvm::Value* EulFloatToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    return llvm::ConstantFP::get(this->generateType(ctx), this->value);
}

llvm::Type* EulFloatToken::generateType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 32: return llvm::Type::getFloatTy(ctx->context);
        case 64: return llvm::Type::getDoubleTy(ctx->context);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64");
    }
}



//ID
llvm::Value* EulIdToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. find the symbol in scope
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, this->name +": Symbol not found.");

    if (sym->llvmValue == nullptr) throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Symbol with name "+ this->name +" does not have a value.");

    //2. We should either return the value as is, or load a variable and return the loading result:
    if (flags & EulCodeGenFlags_LOAD_VAR) {
        auto loadInstr = ctx->builder.CreateLoad(
            sym->llvmValue->getType()->getPointerElementType(),
            sym->llvmValue
        );

        return loadInstr;
    }
    else return sym->llvmValue;
}


//INT
llvm::Value* EulIntToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32:
        case 64: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, !this->isUnsigned));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64");
    }
}


llvm::Type* EulIntToken::generateType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 8:
        case 16:
        case 32:
        case 64: return llvm::IntegerType::get(ctx->context, this->size);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64");
    }
}


//STRING
llvm::Value* EulStringToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //0. Defs
    auto str = this->value;
    auto charType = llvm::IntegerType::get(ctx->context, 8);


    //1. Initialize chars vector
    std::vector<llvm::Constant *> chars(str.length());
    for(unsigned int i = 0; i < str.size(); i++) {
      chars[i] = llvm::ConstantInt::get(charType, str[i]);
    }

    //1b. add a zero terminator too
    chars.push_back(llvm::ConstantInt::get(charType, 0));


    //2. Initialize the string from the characters
    auto stringType = llvm::ArrayType::get(charType, chars.size());

    //3. Insert the constant into the module
    auto globalDeclaration = ctx->makeGlobalLiteral(stringType);
    globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(true);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);


    //3. Return a cast to an i8*
    return llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
}

llvm::Type* EulStringToken::generateType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}