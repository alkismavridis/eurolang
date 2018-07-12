void EulLlvmExporter::makeMain(llvm::Module* module, llvm::IRBuilder<>* builder) {
    //1. Setup function
    llvm::Function* mainFunc = (llvm::Function*)module->getOrInsertFunction("main", llvm::IntegerType::get(module->getContext(), 32), NULL);
    llvm::BasicBlock *block = llvm::BasicBlock::Create(module->getContext(), "entry", mainFunc);
    builder->SetInsertPoint(block);

    //2. add the commands
    builder->CreateRet(
        llvm::ConstantInt::get(llvm::IntegerType::get(module->getContext(), 32), 42, true)
    );
}




void emmitObjCode(llvm::Module* module, const std::string& outputFileName) {
    auto targetTriple = llvm::sys::getDefaultTargetTriple();

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    std::string error;
    auto target = llvm::TargetRegistry::lookupTarget(targetTriple, error);

    // Print an error and exit if we couldn't find the requested target.
    // This generally occurs if we've forgotten to initialise the
    // TargetRegistry or we have a bogus target triple.
    if (!target) {
        llvm:: errs() << error;
        return;
    }


    auto cpu = "generic";
    auto features = "";

    llvm::TargetOptions opt;
    auto rm = llvm::Optional<llvm::Reloc::Model>();
    auto targetMachine = target->createTargetMachine(targetTriple, cpu, features, opt, rm);

    module->setDataLayout(targetMachine->createDataLayout());
    module->setTargetTriple(targetTriple);

    std::error_code ec;
    llvm::raw_fd_ostream dest(outputFileName, ec, llvm::sys::fs::F_None);

    if (ec) {
        llvm::errs() << "Could not open file: " << ec.message();
        return;
    }

    llvm::legacy::PassManager pass;
    auto fileType = llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile;

    if (targetMachine->addPassesToEmitFile(pass, dest, fileType)) {
      llvm::errs() << "TargetMachine can't emit a file of this type";
      return;
    }

    pass.run(*module);
    dest.flush();
}


void omitIRAssembly(llvm::Module* module, const std::string& outputFileName) {
    std::error_code code;
    llvm::raw_fd_ostream out(outputFileName, code, llvm::sys::fs::OpenFlags::F_None);
    module->print(out, nullptr);
}




void EulLlvmExporter::produceOutput(Compiler* compiler, const std::string& outputFileName) {
    std::cout << "I will produce the output" <<std::endl;

    static llvm::LLVMContext context;
    static std::unique_ptr<llvm::Module> dummyModule;
    static llvm::IRBuilder<> builder(context);

    // Make the module, which holds all the code.
    dummyModule = llvm::make_unique<llvm::Module>("main22", context);
    dummyModule->getOrInsertGlobal("myGlob", llvm::Type::getInt64Ty(context));
    dummyModule->getOrInsertGlobal("myGlob2", llvm::Type::getInt32Ty(context));

    //ommit object file
    //emmitObjCode(dummyModule.get(), outputFileName);
    omitIRAssembly(dummyModule.get(), outputFileName);


}