#pragma once


EulCodeGenContext::EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, EulScope* scope) : context(context), builder(context){
    this->module = module;
    this->currentScope = scope;
    this->compiler = compiler;
}
