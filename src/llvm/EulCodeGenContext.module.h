#pragma once


EulCodeGenContext::EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, EulScope* scope) : context(context), builder(context){
    this->module = module;
    this->currentScope = scope;
    this->globalScope = &compiler->program.globalScope;
    this->compiler = compiler;
    this->globIndex = 1;
}




//region TYPE UTILS
llvm::Value* EulCodeGenContext::castValue(llvm::Value* sourceValue, llvm::Type* targetType, EulType* targetEulType) {
    //1. Take care of void case
    const bool isVoid = targetType->isVoidTy();
    if (sourceValue==nullptr && !isVoid) throw EulError(EulErrorType::SEMANTIC, "TODO_type value required, but void was found.");
    if (sourceValue!=nullptr && isVoid) throw EulError(EulErrorType::SEMANTIC, "Void expected, but TODO_typeName was found.");
    if (sourceValue==nullptr && isVoid) return nullptr;

    //2. Check if no cast is needed.
    auto sourceType = sourceValue->getType();
    if (sourceType==targetType) return sourceValue;

    //3. Check basic type castings
    if (targetEulType->getTypeEnum() == EulTypeEnum::INT_TYPE) {
        return this->castToInteger(sourceValue, static_cast<llvm::IntegerType*>(targetType), static_cast<EulIntegerType*>(targetEulType));
    }


    //4. TODO more attempts to convert will go here.


    //5. All failed. throw error.
    throw EulError(EulErrorType::SEMANTIC, "Inconsistent type conversion.");
}

/**
    The second and third parameter MUST be related in the sense that
    targetType == targetEulType->getLlvmType(ctx).

    They are both passed only for efficiency reasons (to be calculated only once)
*/
llvm::Value* EulCodeGenContext::castToInteger(llvm::Value* sourceValue, llvm::IntegerType* targetType, EulIntegerType* targetEulType) {
    //NOTE at the moment only int to int castings are allowed.

    //1. Check that the source type is indeed an integer
    auto sourceType = sourceValue->getType();
    if (!sourceType->isIntegerTy()) throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints can be casted to ints.");
    auto intSourceType = static_cast<llvm::IntegerType*>(sourceType);

    //2. If the target value has less bits than the source, trunk the value
    if (targetEulType->isUnsigned) return this->builder.CreateZExtOrTrunc(sourceValue, targetType);
    else return this->builder.CreateSExtOrTrunc(sourceValue, targetType);
}
//endregion



//region VALUE UTILS
llvm::GlobalVariable* EulCodeGenContext::makeGlobalLiteral(llvm::Type* type) {
    return static_cast<llvm::GlobalVariable*> (
        this->module->getOrInsertGlobal(".glob"+ std::to_string(this->globIndex++), type)
    );
}
//endregion