#pragma once

llvm::Value* EulToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulToken" << std::endl;
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateValue was called, but should not!");
}

llvm::Value* EulCharToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulCharToken" << std::endl;

    //TODO char literals. At the moment we return an Int
    //return llvm::ConstantChar::get(gen->context, llvm::APCharLiteral(this->size, this->value, false));
    return nullptr;

}

llvm::Value* EulFloatToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulFloatToken" << std::endl;

    //TODO Size?
    return llvm::ConstantFP::get(gen->context, llvm::APFloat(this->value));
}

llvm::Value* EulIdToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulIdToken" << std::endl;


    //TODO ids can be many different things. Probably only the AST will know what we really are...
    return nullptr;
}

llvm::Value* EulIntToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulIntToken" << std::endl;
    return llvm::ConstantInt::get(gen->context, llvm::APInt(this->size, this->value, !this->isUnsigned));
}

llvm::Value* EulStringToken::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulStringToken" << std::endl;

    //TODO create string literal
    return nullptr;
}