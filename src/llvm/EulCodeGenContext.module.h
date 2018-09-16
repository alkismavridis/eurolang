#pragma once


EulCodeGenContext::EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, std::shared_ptr<EulScope> scope, std::shared_ptr<EulFunction> func) : context(context), builder(context){
    this->module = module;
    this->currentScope = scope;
    this->globalScope = compiler->program.globalScope;
    this->compiler = compiler;
    this->globIndex = 1;
    this->currentFunction = func;
}


//region VALUE UTILS
llvm::GlobalVariable* EulCodeGenContext::makeGlobalLiteral(llvm::Type* type) {
    return static_cast<llvm::GlobalVariable*> (
        this->module->getOrInsertGlobal(".glob"+ std::to_string(this->globIndex++), type)
    );
}
//endregion