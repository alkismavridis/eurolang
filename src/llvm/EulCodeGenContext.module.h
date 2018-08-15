#pragma once


EulCodeGenContext::EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, EulScope* scope) : context(context), builder(context){
    this->module = module;
    this->currentScope = scope;
    this->compiler = compiler;
    this->globIndex = 1;
}




//region TYPE UTILS
llvm::Value* EulCodeGenContext::castValue(llvm::Value* sourceValue, llvm::Type* targetType) {
    //1. Take care of void case
    const bool isVoid = targetType->isVoidTy();
    if (sourceValue==nullptr && !isVoid) throw EulError(EulErrorType::SEMANTIC, "TODO_type value required, but void was found");
    if (sourceValue!=nullptr && isVoid) throw EulError(EulErrorType::SEMANTIC, "Void expected, but TODO_typeName was found");
    if (isVoid && sourceValue==nullptr) return nullptr;

    //2. Check if no cast is needed.
    auto sourceType = sourceValue->getType();
    if (sourceType==targetType) return sourceValue;



    //3. Check basic type castings
    if (targetType->isIntegerTy()) return this->castToInteger(sourceValue, (llvm::IntegerType*)targetType);


    throw EulError(EulErrorType::SEMANTIC, "Inconsistent types found.");
}


llvm::Value* EulCodeGenContext::castToInteger(llvm::Value* sourceValue, llvm::IntegerType* targetType) {
    //NOTE at the moment only int to int castings are allowed.
    auto sourceType = sourceValue->getType();
    if (!sourceType->isIntegerTy()) throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT_IMPLEMENTED only ints can be casted to ints.");
    auto intSourceType = (llvm::IntegerType*) sourceType;

    //1. If the target value has less bits than the source, trunk the value
    //TODO CreateSExtOrTrunc or CreateZExtOrTrunc?
    return this->builder.CreateSExtOrTrunc(sourceValue, targetType);
}
//endregion



//region VALUE UTILS
llvm::GlobalVariable* EulCodeGenContext::makeGlobalLiteral(llvm::Type* type) {
    return (llvm::GlobalVariable*) this->module->getOrInsertGlobal(".glob"+ std::to_string(this->globIndex++), type);
}
//endregion