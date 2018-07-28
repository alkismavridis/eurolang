#pragma once


EulCodeGenContext::EulCodeGenContext(llvm::LLVMContext* context, llvm::Module* module) : builder(*context) {
    this->context = context;
    this->module = module;
}


EulType* EulCodeGenContext::createEulType(const std::string& typeName, bool assertExistence) {
    llvm::IntegerType::get(*this->context, 32); //TODO dummy int type.
}
