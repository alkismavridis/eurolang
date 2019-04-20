#pragma once


//region LIFE CYCLE


//endregion



//region CORE FUNCTIONS
std::shared_ptr<EulType> EulType::getPointerTo(unsigned char depth) {
    return std::make_shared<EulPointerType>(this, depth);
}

EulTypeEnum EulType::getTypeEnum() { return EulTypeEnum::VOID_TYPE; }

EulNodeType EulType::getNodeType() { return EulNodeType::TYPE; }

bool EulType::isEulType(EulNode* tok) {
    return tok->getNodeType() == EulNodeType::TYPE;
}
//endregion



//region CODE GENERATION
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

llvm::Value* EulType::castValue(llvm::Value* sourceValue, EulType* sourceType, bool isExplicit, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::castValue was called, but it should not.");
}

llvm::Type* EulType::getLlvmType(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulType::getLlvmType was called.");
}
//endregion


//region SERIALIZATION
//endregion
