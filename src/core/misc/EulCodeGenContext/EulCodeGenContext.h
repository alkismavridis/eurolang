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

    NOTE one EulCodeGenContext will be instantiated per module.
*/
class EulCodeGenContext {
    //region FIELDS
    //PROGRAM SCOPED FIELDS
    public: llvm::LLVMContext& context;
    public: llvm::IRBuilder<> builder;
    public: llvm::Module* module;
    public: std::vector<std::shared_ptr<llvm::GlobalVariable>> moduleGlobals; //we collect them to be deleted at the end of the scope of this object

    public: std::shared_ptr<EulScope> currentScope;
    public: std::shared_ptr<EulScope> globalScope; //this equals by definition to compiler->program.globalScope, but for efficiency, we store a pointer to it here for quicker access.
    public: std::shared_ptr<EulFunction> currentFunction;

    public: Compiler* compiler;
    public: int globIndex;
    //endregion



    //region LIFE CYCLE
    public: EulCodeGenContext(Compiler* compiler, llvm::LLVMContext& context, llvm::Module* module, std::shared_ptr<EulScope> scope, std::shared_ptr<EulFunction> currentFunction);
    //endregion



    //region VALUE UTILS
    public: llvm::GlobalVariable* makeGlobalLiteral(llvm::Type* type);
    //endregion
};