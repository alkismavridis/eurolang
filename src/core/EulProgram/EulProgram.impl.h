#pragma once



//region NATIVE TYPES
EulNativeTypes::EulNativeTypes() {
    this->voidType = std::make_shared<EulVoidType>();

    this->int8Type = std::make_shared<EulIntegerType>(8, false);
    this->int16Type = std::make_shared<EulIntegerType>(16, false);
    this->int32Type = std::make_shared<EulIntegerType>(32, false);
    this->int64Type = std::make_shared<EulIntegerType>(64, false);
    this->intType = std::make_shared<EulIntegerType>(EUL_LANG_DEFAULT_INT_SIZE, false);

    this->uint8Type = std::make_shared<EulIntegerType>(8, true);
    this->uint16Type = std::make_shared<EulIntegerType>(16, true);
    this->uint32Type = std::make_shared<EulIntegerType>(32, true);
    this->uint64Type = std::make_shared<EulIntegerType>(64, true);
    this->uintType = std::make_shared<EulIntegerType>(EUL_LANG_DEFAULT_INT_SIZE, true);


    this->float32Type = std::make_shared<EulFloatType>(32);
    this->float64Type = std::make_shared<EulFloatType>(64);
    this->floatType = std::make_shared<EulFloatType>(EUL_LANG_DEFAULT_FLOAT_SIZE);

    this->char8Type = std::make_shared<EulCharType>(8);
    this->char16Type = std::make_shared<EulCharType>(16);
    this->char32Type = std::make_shared<EulCharType>(32);
    this->charType = std::make_shared<EulCharType>(8);

    this->booleanType = std::make_shared<EulBooleanType>();
    this->stringType = std::make_shared<EulStringType>();
}
//endregion



//region LIFE CYCLE
EulProgram::EulProgram() : globalScope(nullptr) {
    this->globalScope = std::make_shared<EulScope>(nullptr);
    this->initGlobals();
}


void EulProgram::initGlobals() {
    //Define basic Integer types
    this->globalScope->declare("void", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.voidType));

    this->globalScope->declare("Int8", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.int8Type));
    this->globalScope->declare("Int16", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.int16Type));
    this->globalScope->declare("Int32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.int32Type));
    this->globalScope->declare("Int64", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.int64Type));
    this->globalScope->declare("Int", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.intType));

    this->globalScope->declare("UInt8", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.uint8Type));
    this->globalScope->declare("UInt16", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.uint16Type));
    this->globalScope->declare("UInt32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.uint32Type));
    this->globalScope->declare("UInt64", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.uint64Type));
    this->globalScope->declare("UInt", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.uintType));

    this->globalScope->declare("Float32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.float32Type));
    this->globalScope->declare("Float64", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.float64Type));
    this->globalScope->declare("Float", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.floatType));


    this->globalScope->declare("Char8", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.char8Type));
    this->globalScope->declare("Char16", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.char16Type));
    this->globalScope->declare("Char32", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.char32Type));
    this->globalScope->declare("Char", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.charType));

    this->globalScope->declare("String", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.stringType));
    this->globalScope->declare("Bool", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, nullptr, this->nativeTypes.booleanType));
}

void EulProgram::reset() {
    this->sources.clear();
    this->globalScope->reset();
    this->initGlobals();
}
//endregion




//region GLOBAL DECLARATIONS
//endregion




//region GETTERS
std::shared_ptr<EulSourceFile> EulProgram::getSource(const std::string& id, unsigned char createIfNotExists) {
    //try finding the file
    auto entry = this->sources.find(id);
    if(entry != this->sources.end()) return entry->second;

    //we did not find the token. What we should now do, depends on createIfNotExists.
    if (!createIfNotExists) return 0;

    //we create a token, add it on our list, and return it.
    auto ret = std::make_shared<EulSourceFile>(id, this->globalScope);
    this->sources[id] = ret;
    return ret;
}


/**
  Will be probably called by the Compiler object every time it needs to get the next source file.
  returns null if all files are parsed.
*/
std::shared_ptr<EulSourceFile> EulProgram::nextPendingSource() {
    for (auto const& e : this->sources) {
        if ( !e.second->isParsed ) return e.second;
    }

    //all files are parsed. return null.
    return 0;
}

std::shared_ptr<EulSourceFile> EulProgram::getEntryPoint() {
    auto firstEntry = this->sources.begin();
    if (firstEntry == this->sources.end()) return nullptr;
    return firstEntry->second;
}
//endregion




//region GENERATOR SETUP
void EulProgram::declareClibSymbols(EulCodeGenContext* ctx) {
    //1. Define exit()
    auto eulFuncType = std::make_shared<EulFunctionType>(ctx->compiler->program.nativeTypes.voidType);  //returns void
    eulFuncType->argTypes.push_back(ctx->compiler->program.nativeTypes.int32Type);
    auto declaration = llvm::Function::Create(static_cast<llvm::FunctionType*>(eulFuncType->getLlvmType(ctx)), llvm::Function::ExternalLinkage, "exit", ctx->module);
    this->globalScope->declare("exit", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, eulFuncType, declaration));


    //2. define print (puts)
    eulFuncType = std::make_shared<EulFunctionType>(ctx->compiler->program.nativeTypes.int32Type);  //returns Int32
    eulFuncType->argTypes.push_back(ctx->compiler->program.nativeTypes.stringType);
    declaration = llvm::Function::Create(static_cast<llvm::FunctionType*>(eulFuncType->getLlvmType(ctx)), llvm::Function::ExternalLinkage, "puts", ctx->module);
    this->globalScope->declare("print", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, eulFuncType, declaration));

    //2. define printf TODO
    //eulFuncType = std::make_shared<EulFunctionType>(ctx->compiler->program.nativeTypes.int32Type);  //returns Int32
    //eulFuncType->argTypes.push_back(ctx->compiler->program.nativeTypes.stringType);
    //declaration = llvm::Function::Create(static_cast<llvm::FunctionType*>(eulFuncType->getLlvmType(ctx)), llvm::Function::ExternalLinkage, "printf", ctx->module);
    //this->globalScope->declare("printf", std::make_shared<EulSymbol>(yy::EulParser::token::VAL, eulFuncType, declaration));
}


std::shared_ptr<EulFunction> EulProgram::makeMain(EulCodeGenContext* ctx) {
    //1. Create the eul function
    std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> mainParams = nullptr; //TODO main accepts argv and argc
    auto mainEulFunc = std::make_shared<EulFunction>(
        std::make_shared<EulFunctionType>(ctx->compiler->program.nativeTypes.int32Type, mainParams),
        mainParams,
        nullptr //main is a special case. We do not need to assign a block to it. By default this is the whole content of all source files.
    );

    //2. Create the llvm definition
    llvm::Function* mainFunc = static_cast<llvm::Function*>(
        ctx->module->getOrInsertFunction(
            "main",
            llvm::IntegerType::get(ctx->context, 32)
        )
    );

    //3. Setup basic block
    llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx->context, "entry", mainFunc);
    ctx->builder.SetInsertPoint(block);

    return mainEulFunc;
}


/**
    This represents the real entry point of the program. This function never returns.
    It just calls main, and then performs a system call in order to terminate.
*/
void EulProgram::makeEntryPoint(EulCodeGenContext* ctx) {
    //1. Create the llvm function
    llvm::Function* entryPointFnc = static_cast<llvm::Function*>(ctx->module->getOrInsertFunction("_startEul", llvm::IntegerType::get(ctx->context, 32)));
    llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx->context, "entry", entryPointFnc);
    ctx->builder.SetInsertPoint(block);


    //2. Call main
    auto mainFunc = static_cast<llvm::Function*>(ctx->module->getOrInsertFunction("main", llvm::IntegerType::get(ctx->context, 32)));
    auto mainReturnValue = ctx->builder.CreateCall(mainFunc);



    //3. Call exit
    auto exitFunc = static_cast<llvm::Function*>(ctx->module->getNamedValue("exit"));
    ctx->builder.CreateCall(exitFunc, mainReturnValue);


    //5. Add return statement.
    auto zero = llvm::ConstantInt::get(llvm::IntegerType::get(ctx->context, 32), 0, true);
    ctx->builder.CreateRet(zero);
}
//endregion



//region AST PARSING
void EulProgram::emmitObjCode(EulCodeGenContext* ctx, const std::string& outputFileName) {
    //TODO we must deal with multiple modules being emitted.

    auto targetTriple = llvm::sys::getDefaultTargetTriple();

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

    ctx->module->setDataLayout(targetMachine->createDataLayout());
    ctx->module->setTargetTriple(targetTriple);

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

    // Promote allocas to registers.
    pass.add(llvm::createPromoteMemoryToRegisterPass());
    // Do simple "peephole" optimizations and bit-twiddling optzns.
    pass.add(llvm::createInstructionCombiningPass());
    // Reassociate expressions.
    pass.add(llvm::createReassociatePass());
    // Eliminate Common SubExpressions.
    pass.add(llvm::createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    pass.add(llvm::createCFGSimplificationPass());

    pass.run(*ctx->module);
    dest.flush();
}


void EulProgram::emmitIRAssembly(EulCodeGenContext* ctx, const std::string& outputFileName) {
    std::error_code code;
    llvm::raw_fd_ostream out(outputFileName, code, llvm::sys::fs::OpenFlags::F_None);

    //ctx->module->print(llvm::errs(), nullptr);
    ctx->module->print(out, nullptr);
}
//endregion