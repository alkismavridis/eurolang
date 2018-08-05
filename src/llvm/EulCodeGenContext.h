#pragma once


/**
    This is a very important class.
    It represents the bridge between the AST and llvm.

    This object will be used once the AST has been completelly built,
    and the parsing of AST has started.
    At this point, llvmContext, modules and builders will be already in place, and operating.

    This means that the AST needs a way to communicate with llvm.
    A pointer of EulCodeGenContext is being passed to all AST methods.

    At the moment it is stateless.
    The state lies in the underlying llvm library types: LLVMContext, Module and IRBuilder
*/
class EulCodeGenContext {
    //region FIELDS
    public: llvm::LLVMContext& context;
    public: llvm::IRBuilder<> builder;
    public: llvm::Module* module;

    public: EulScope* currentScope;
    public: Compiler* compiler;
    //endregion



    //region LIFE CYCLE
    public: EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, EulScope* scope);
    //endregion
};