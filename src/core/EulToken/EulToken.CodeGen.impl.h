#pragma once

llvm::Value* EulToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateValue was called, but should not!");
}

std::shared_ptr<EulType> EulToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    throw EulError(EulErrorType::SEMANTIC, "EulToken::getEulType was called, but should not!");
}



//CHAR
llvm::Value* EulCharToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, false));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32.");
    }
}

std::shared_ptr<EulType> EulCharToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 8: return ctx->compiler->program.nativeTypes.char8Type;
        case 16: return ctx->compiler->program.nativeTypes.char16Type;
        case 32: return ctx->compiler->program.nativeTypes.char32Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32.");
    }
}



//FLOAT
llvm::Value* EulFloatToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    auto llvmType = this->getEulType(ctx, 0)->getLlvmType(ctx);
    return llvm::ConstantFP::get(llvmType, this->value);
}

std::shared_ptr<EulType> EulFloatToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 32: return ctx->compiler->program.nativeTypes.float32Type;
        case 64: return ctx->compiler->program.nativeTypes.float64Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64.");
    }
}



//ID
llvm::Value* EulIdToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //1. find the symbol in scope
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, this->name +": Symbol not found.");


    //2. We should either return the value as is, or load a variable and return the loading result:
    if (flags & EulCodeGenFlags_LOAD_VAR) {
        if (sym->llvmValue == nullptr)
            throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Symbol with name "+ this->name +" does not have a value.");

        auto loadInstr = ctx->builder.CreateLoad(
            sym->llvmValue->getType()->getPointerElementType(),
            sym->llvmValue
        );

        return loadInstr;
    }
    else return sym->llvmValue;
}

std::shared_ptr<EulType> EulIdToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, this->name +": Symbol not found.");

    return sym->varType;
}


//INT
llvm::Value* EulIntToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32:
        case 64: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, !this->isUnsigned));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64.");
    }
}


std::shared_ptr<EulType> EulIntToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 8: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint8Type : ctx->compiler->program.nativeTypes.int8Type;
        case 16: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint16Type : ctx->compiler->program.nativeTypes.int16Type;
        case 32: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint32Type : ctx->compiler->program.nativeTypes.int32Type;
        case 64: return this->isUnsigned? ctx->compiler->program.nativeTypes.uint64Type : ctx->compiler->program.nativeTypes.int64Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid integer size: " + std::to_string(this->size)+". Please use one of 8, 16, 32, 64.");
    }
}




//BOOLEAN
llvm::Value* EulBooleanToken::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    return llvm::ConstantInt::get(ctx->context, llvm::APInt(1, this->value? 1 : 0, true));
}

std::shared_ptr<EulType> EulBooleanToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    return ctx->compiler->program.nativeTypes.booleanType;
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
    globalDeclaration->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);


    //3. Return a cast to an i8*
    return llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
}

std::shared_ptr<EulType> EulStringToken::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    return ctx->compiler->program.nativeTypes.stringType;
}