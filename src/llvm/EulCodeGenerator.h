class EulCodeGenerator {
    //region FIELDS
    public: llvm::LLVMContext context;
    public: llvm::IRBuilder<> builder;
    public: Compiler* compiler;
    //endregion



    //region LIFE CYCLE
    public: EulCodeGenerator(Compiler* comp);
    //endregion



    //region OUTPUT SETUP
    private: void makeMain(llvm::Module* module, llvm::IRBuilder<>* builder);
    //endregion



    //region AST PARSING
    private: void doPreParsing(EulSourceFile* file);
    private: void parse(EulSourceFile* file);
    //endregion







    //region API
    public: void produceOutput(const std::string& outputFileName);
    //endregion



};