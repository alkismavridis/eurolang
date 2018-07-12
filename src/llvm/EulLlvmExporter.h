class EulLlvmExporter {

    //region OUTPUT SETUP
    private: void makeMain(llvm::Module* module, llvm::IRBuilder<>* builder);
    //endregion








    //region API
    public: void produceOutput(Compiler* compiler, const std::string& outputFileName);
    //endregion



};