#pragma once

//region TYPE CASTINGS
/**
    If this function returns without throwing an exception,
    it means that both left type and right type are integer types, and that their sizes are valid.
*/
std::shared_ptr<EulIntegerType> EulType::doCommonIntMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx) {
    //1. Check that operands are indeed integer types
    if (left->getTypeEnum()!=EulTypeEnum::INT_TYPE || right->getTypeEnum()!=EulTypeEnum::INT_TYPE)
        throw EulError(EulErrorType::SEMANTIC, "Invalid conversion to int.");

    //2. Cast them into integers
    const auto leftAsInt = static_cast<EulIntegerType*>(left.get());
    const auto rightAsInt = static_cast<EulIntegerType*>(right.get());

    //3. Decide the resulting size, and whether the result is unsigned or not.
    // The biggest one wins for size, and unsigned wins over signed.
    unsigned char resultSize = (leftAsInt->size > rightAsInt->size) ?
        leftAsInt->size :
        rightAsInt->size;
    bool isResultUnsigned = leftAsInt->isUnsigned || rightAsInt->isUnsigned;

    //4. Find the result type, according to the above constrains, and return in
    switch(resultSize) {
        case 8:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint8Type :
                ctx->compiler->program.nativeTypes.int8Type;

        case 16:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint16Type :
                ctx->compiler->program.nativeTypes.int16Type;

        case 32:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint32Type :
                ctx->compiler->program.nativeTypes.int32Type;

        case 64:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint64Type :
                ctx->compiler->program.nativeTypes.int64Type;

        default: throw EulError(EulErrorType::SEMANTIC, "Wrong int size: " + std::to_string(resultSize));
    }
}


std::shared_ptr<EulFloatType> EulType::doCommonFloatMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx) {
    //1. Check that operands are indeed float types
    if (left->getTypeEnum()!=EulTypeEnum::FLOAT_TYPE || right->getTypeEnum()!=EulTypeEnum::FLOAT_TYPE)
        throw EulError(EulErrorType::SEMANTIC, "Invalid conversion to float.");

    //2. Cast them into integers
    const auto leftAsFloat = static_cast<EulFloatType*>(left.get());
    const auto rightAsFloat = static_cast<EulFloatType*>(right.get());

    //3. Fins the biggest size
    auto maxSize = leftAsFloat->size > rightAsFloat->size?
        leftAsFloat->size :
        rightAsFloat->size;

    //4. Return a type based on its size
    switch(maxSize) {
        case 32: return ctx->compiler->program.nativeTypes.float32Type;
        case 64: return ctx->compiler->program.nativeTypes.float64Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Wrong float size: " + std::to_string(maxSize));
    }
}



std::shared_ptr<EulType> EulType::doCommonNumberMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx) {
    auto leftTypeEnum = left->getTypeEnum();
    auto rightTypeEnum = right->getTypeEnum();

    if (leftTypeEnum == EulTypeEnum::INT_TYPE) {
        if (rightTypeEnum == EulTypeEnum::INT_TYPE) return EulType::doCommonIntMerging(left, right, ctx);
        if (rightTypeEnum == EulTypeEnum::FLOAT_TYPE) return right;
        throw EulError(EulErrorType::SEMANTIC, "Invalid conversion to number.");
    }

    if (leftTypeEnum == EulTypeEnum::FLOAT_TYPE) {
        if (rightTypeEnum == EulTypeEnum::INT_TYPE) return left;
        if (rightTypeEnum == EulTypeEnum::FLOAT_TYPE) return EulType::doCommonFloatMerging(left, right, ctx);
        throw EulError(EulErrorType::SEMANTIC, "Invalid conversion to number.");
    }

    throw EulError(EulErrorType::SEMANTIC, "Invalid conversion to number.");
}
//endregion




//region BASE CLASS
llvm::Value* EulType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::castValue was called, but it should not.");
}

llvm::Type* EulType::getLlvmType(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::getLlvmType was called.");
}
//endregion




//region CHAR TYPES
llvm::Value* EulCharType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulCharType::castValue.");
}

llvm::Type* EulCharType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}
//endregion



//region INTEGER TYPES
llvm::Value* EulIntegerType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    //NOTE at the moment only int to int castings are allowed.

    //1. Check that the source type is indeed an integer
    if (sourceType->getTypeEnum() != EulTypeEnum::INT_TYPE) throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints can be casted to ints.");

    //2. If the target value has less bits than the source, trunk the value
    auto targetLlvmType = this->getLlvmType(ctx);
    if (this->isUnsigned) return ctx->builder.CreateZExtOrTrunc(sourceValue, targetLlvmType);
    else return ctx->builder.CreateSExtOrTrunc(sourceValue, targetLlvmType);
}

llvm::Type* EulIntegerType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size);
}

//endregion



//region FLOAT TYPES
llvm::Value* EulFloatType::castIntToFloatValue(llvm::Value* sourceValue, EulIntegerType* sourceType, EulCodeGenContext* ctx) {
    //Int casting takes in account whether the source integer type is unsigned or not.
    //Different llvm instructions are involved if it is so.
    if (sourceType->isUnsigned) return ctx->builder.CreateUIToFP(sourceValue, this->getLlvmType(ctx));
    else return ctx->builder.CreateSIToFP(sourceValue, this->getLlvmType(ctx));
}

llvm::Value* EulFloatType::castFloatToFloatValue(llvm::Value* sourceValue, EulFloatType* sourceType, EulCodeGenContext* ctx) {
    if (this->size == sourceType->size) return sourceValue;
    else if(this->size < sourceType->size) return ctx->builder.CreateFPTrunc(sourceValue, this->getLlvmType(ctx));
    else return ctx->builder.CreateFPExt(sourceValue, this->getLlvmType(ctx));
}

llvm::Value* EulFloatType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    //NOTE at the moment only int->float and float->floats castings are allowed.

    //1. Check that the source type is indeed an integer
    switch (sourceType->getTypeEnum()) {
        case EulTypeEnum::INT_TYPE:
            return this->castIntToFloatValue(sourceValue, static_cast<EulIntegerType*>(sourceType), ctx);

        case EulTypeEnum::FLOAT_TYPE:
             return this->castFloatToFloatValue(sourceValue, static_cast<EulFloatType*>(sourceType), ctx);

        default: throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints and floats can be casted to float.");
    }
}

llvm::Type* EulFloatType::getLlvmType(EulCodeGenContext* ctx) {
    switch(this->size) {
        case 32: return llvm::Type::getFloatTy(ctx->context);
        case 64: return llvm::Type::getDoubleTy(ctx->context);
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid floating point size: " + std::to_string(this->size)+". Please use one of 32, 64.");
    }
}
//endregion


//region FUNCTION TYPES
llvm::Value* EulFunctionType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulFunctionType::castValue.");
}

llvm::Type* EulFunctionType::getLlvmType(EulCodeGenContext* ctx) {
    //1. Build argument list
    std::vector<llvm::Type*> llvmArgList;
    for (auto const& argType : this->argTypes) llvmArgList.push_back(argType->getLlvmType(ctx));

    auto ret = llvm::FunctionType::get(
        this->retType->getLlvmType(ctx),
        llvm::ArrayRef<llvm::Type*>(llvmArgList),
        false
    );

    return ret;
}
//endregion



//region NAMED TYPES
llvm::Value* EulNamedType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulNamedType::castValue.");
}

llvm::Type* EulNamedType::getLlvmType(EulCodeGenContext* ctx) {
    return ctx->module->getTypeByName(this->name);
}
//endregion



//region POINTER TYPES
llvm::Value* EulPointerType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED EulPointerType::castValue.");
}

llvm::Type* EulPointerType::getLlvmType(EulCodeGenContext* ctx) {
    auto type = this->contentType->getLlvmType(ctx);
    for (int i = this->depth; i--;) type = type->getPointerTo();
    return type;
}
//endregion



//region STRING TYPES
llvm::Value* EulStringType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceType->getTypeEnum() != EulTypeEnum::STRING_TYPE)
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED Only string can be casted to string.");

    return sourceValue;
}

llvm::Type* EulStringType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, 8)->getPointerTo();
}
//endregion


//region BOOLEAN TYPE
llvm::Value* EulBooleanType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceType->getTypeEnum() == EulTypeEnum::BOOLEAN_TYPE) return sourceValue;
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "Cannot cast a non boolean value to boolean.");
}

llvm::Type* EulBooleanType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::Type::getInt1Ty(ctx->context);
}
//endregion


//region VOID TYPE
llvm::Value* EulVoidType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    if (sourceValue != nullptr)
        throw EulError(EulErrorType::NOT_IMPLEMENTED, "Cannot cast a value to void.");
    return nullptr;
}

llvm::Type* EulVoidType::getLlvmType(EulCodeGenContext* ctx) {
    return llvm::Type::getVoidTy(ctx->context);
}
//endregion