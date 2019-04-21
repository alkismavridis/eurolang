#pragma once



class EulProgramTest {

    //region SOURCE FILE ACCESSING
    public: void static getAndCreateTest(const std::string& t) {
        EulProgram program;

        //test initial state
        Assert::equals(0, program.sources.size(), t + "A1");

        //test getting without creating while list is empty.
        Assert::null( program.getSource("someFileName.eul", 0).get(), t + "A2");
        Assert::equals(0, program.sources.size(), t + "A3");

        //test getOrCreate
        auto firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t +"B1");
        Assert::equals(1, program.sources.size(), t + "B2");

        //get it with createFlag off.
        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile.get(), t + "C1");
        Assert::equals("someFileName.eul", firstFile->id, t + "C2");
        Assert::equals(1, program.sources.size(), t + "C3");

        //get it with createFlag on
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t + "D1");
        Assert::equals("someFileName.eul", firstFile->id, t + "D2");
        Assert::equals(1, program.sources.size(), t + "D3");

        //ask for a file that does not exists
        firstFile = program.getSource("someFileName2.eul", 0);
        Assert::null(firstFile.get(), t + "E1");
        Assert::equals(1, program.sources.size(), t + "E2");

        //create a second file
        auto secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile.get(), t + "F1");
        Assert::equals("someFileName2.eul", secondFile->id, t + "F2");
        Assert::equals(2, program.sources.size(), t + "F3");

        //test getters
        firstFile = program.getSource("someFileName.eul", 1);
        Assert::notNull(firstFile.get(), t + "G1");
        Assert::equals("someFileName.eul", firstFile->id, t + "G2");

        firstFile = program.getSource("someFileName.eul", 0);
        Assert::notNull(firstFile.get(), t + "G3");
        Assert::equals("someFileName.eul", firstFile->id, t + "G4");

        secondFile = program.getSource("someFileName2.eul", 1);
        Assert::notNull(secondFile.get(), t + "G5");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G6");

        secondFile = program.getSource("someFileName2.eul", 0);
        Assert::notNull(secondFile.get(), t + "G7");
        Assert::equals("someFileName2.eul", secondFile->id, t + "G8");

        Assert::equals(2, program.sources.size(), t + "G9");
    }

    public: void static nextPendingSourceTest(const std::string& t) {
        EulProgram program;

        //add 3 files
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        auto file3 = program.getSource("someFileName3.eul", 1);
        Assert::notNull(file1.get(), t + "A1");
        Assert::notNull(file2.get(), t + "A2");
        Assert::notNull(file3.get(), t + "A3");
        Assert::equals(3, program.sources.size(), t + "A4");

        //test nextPending getter
        Assert::equals(file1.get(), program.nextPendingSource().get(), t + "B1");

        file1->isParsed = 1;
        Assert::equals(file2.get(), program.nextPendingSource().get(), t + "B2");

        file2->isParsed = 1;
        Assert::equals(file3.get(), program.nextPendingSource().get(), t + "B3");

        file3->isParsed = 1;
        Assert::null(program.nextPendingSource().get(), t + "B4");
    }

    public: static void getEntryPointTest(const std::string& t) {
        EulProgram program;

        //1. Get the entry point. null should be returned at this point.
        Assert::null(program.getEntryPoint().get(), t+"A1");

        //2. Declare 3 files. The first one must be the entry point
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        auto file3 = program.getSource("someFileName3.eul", 1);
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A2");

        //3. Check that this is not influenced by parsed flags etc.
        file1->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A3");
        file2->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A4");
        file3->isParsed = 1;
        Assert::equals(file1.get(), program.getEntryPoint().get(), t+"A5");
    }
    //endregion


    public: static void globalsInitTest(const std::string& t) {
        EulProgram program;

        //1. Check that native types are initialized.
        Assert::notNull(program.nativeTypes.int32Type.get(), t+"A1");
        Assert::notNull(program.nativeTypes.uint64Type.get(), t+"A2");
        Assert::notNull(program.nativeTypes.stringType.get(), t+"A3");

        //2. Check that symbols are inserted into the scope
        Assert::equals(program.globalScope->getOwnSymbolAsType("Int32"), program.nativeTypes.int32Type.get(), t+"B1");
        Assert::equals(program.globalScope->getOwnSymbolAsType("UInt64"), program.nativeTypes.uint64Type.get(), t+"B2");
        Assert::equals(program.globalScope->getOwnSymbolAsType("String"), program.nativeTypes.stringType.get(), t+"B3");
    }

    public: static void resetTest(const std::string& t) {
        EulProgram program;

        //1. Add 2 source files and some symbols on the global scope
        auto file1 = program.getSource("someFileName1.eul", 1);
        auto file2 = program.getSource("someFileName2.eul", 1);
        program.globalScope->declare("someNewSymbol", std::make_shared<EulSymbol>(yy::EulParser::token::VAR, nullptr, std::make_shared<EulStringNode>("123")));

        Assert::notNull(program.getSource("someFileName1.eul", 0).get(), t+"A1");
        Assert::notNull(program.globalScope->getOwnSymbol("someNewSymbol").get(), t+"A2");
        Assert::notNull(program.globalScope->getOwnSymbol("Int32").get(), t+"A3");


        //2. Reset. Source files and the "someNewSymbol" symbol should disappear.
        program.reset();
        Assert::null(program.getSource("someFileName1.eul", 0).get(), t+"B1");
        Assert::null(program.globalScope->getOwnSymbol("someNewSymbol").get(), t+"B2");
        Assert::notNull(program.globalScope->getOwnSymbol("Int32").get(), t+"B3"); //Native types should be still here.
    }


    //region CODE GEN TESTS
    public: static void declareClibSymbolsTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Call the function
        comp.program.declareClibSymbols(&ctx);

        //2. Assert that symbols are inserted into scope, and into the llvm module
        //exit(Int32)
        auto eulSymbol = comp.program.globalScope->getOwnSymbol("exit");
        Assert::notNull(eulSymbol.get(), t+"A1 exit is defined in global scope");
        Assert::equals(yy::EulParser::token::VAL, eulSymbol->changeType, t+"A2 is val");
        Assert::enumEquals(EulTypeEnum::FUNCTION_TYPE, eulSymbol->varType->getTypeEnum(), t+"A3 is function");

        auto asFuncType = static_cast<EulFunctionType*>(eulSymbol->varType.get());
        Assert::equals(comp.program.nativeTypes.voidType.get(), asFuncType->retType.get(), t+"A4 exit is void");
        Assert::equals(1, asFuncType->argTypes.size(), t+"A5 exit has one param");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), asFuncType->argTypes[0].get(), t+"A6 exit param is int");
        Assert::notNull(eulSymbol->llvmValue, t+"A7 llvm value is set");
        Assert::equals(ctx.module->getNamedValue("exit"), eulSymbol->llvmValue, t+"A8 exit is defined in llvm module");

        //print(String)
        eulSymbol = comp.program.globalScope->getOwnSymbol("print");
        Assert::notNull(eulSymbol.get(), t+"B1 print is defined in global scope");
        Assert::equals(yy::EulParser::token::VAL, eulSymbol->changeType, t+"B2 is val");
        Assert::enumEquals(EulTypeEnum::FUNCTION_TYPE, eulSymbol->varType->getTypeEnum(), t+"B3 is function");

        asFuncType = static_cast<EulFunctionType*>(eulSymbol->varType.get());
        Assert::equals(comp.program.nativeTypes.int32Type.get(), asFuncType->retType.get(), t+"B4 print returns int");
        Assert::equals(1, asFuncType->argTypes.size(), t+"B5 exit has one param");
        Assert::equals(comp.program.nativeTypes.stringType.get(), asFuncType->argTypes[0].get(), t+"B6 print param is String");
        Assert::notNull(eulSymbol->llvmValue, t+"B7 llvm value is set");
        Assert::equals(ctx.module->getNamedValue("puts"), eulSymbol->llvmValue, t+"B8 puts is defined in llvm module");
    }


    public: static void makeMainTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Call the function
        comp.program.makeMain(&ctx);

        //2. Assert the result
        auto mainFunc = ctx.module->getNamedValue("main");
        Assert::notNull(mainFunc, t+"A1 main is not null");
        Assert::that(llvm::Function::classof(mainFunc), t+"A2 main is a function");

        auto asFunction = static_cast<llvm::Function*>(mainFunc);
        Assert::equals(llvm::IntegerType::get(ctx.context, 32), asFunction->getReturnType(), t+"A3 main returns int");
        Assert::equals(0, asFunction->arg_size(), t+"A4 main has no args TODO we must pass an array of strings as parameters to the program");
        Assert::equals(1, asFunction->size(), t+"A5 main has a basic block");
    }

    public: static void makeEntryPoint(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);
        comp.program.declareClibSymbols(&ctx);
        comp.program.makeMain(&ctx);

        //1. Call the function
        comp.program.makeEntryPoint(&ctx);

        //2. Assert the entry point function
        auto entryPoint = ctx.module->getNamedValue("_startEul");
        Assert::notNull(entryPoint, t+"A1 _startEul is not null");
        Assert::that(llvm::Function::classof(entryPoint), t+"A2 _startEul is a function");

        auto asFunction = static_cast<llvm::Function*>(entryPoint);
        Assert::equals(0, asFunction->arg_size(), t+"A3 _startEul has no args");
        Assert::equals(1, asFunction->size(), t+"A4 _startEul has a basic block");

        //3. Assert its commands
        auto& block = * asFunction->begin();
        Assert::equals(3, block.size(), t+"B1 _startEul has 3 commands");

        //calling main
        auto iterator = block.begin();
        auto command1 = &(*iterator);
        Assert::that(llvm::CallInst::classof(command1), t+"B2 first command a function call");

        auto asFuncCall = static_cast<llvm::CallInst*>(command1);
        Assert::equals(llvm::IntegerType::get(ctx.context, 32), asFuncCall->getType(), t+"B3 the call returns i32");
        Assert::equals(ctx.module->getNamedValue("main"), asFuncCall->getCalledFunction(), t+"B3 the call is to main");

        iterator++;
        auto command2 = &(*iterator);
        Assert::that(llvm::CallInst::classof(command2), t+"C1 second command a function call");

        asFuncCall = static_cast<llvm::CallInst*>(command2);
        Assert::equals(llvm::Type::getVoidTy(ctx.context), asFuncCall->getType(), t+"C2 call returns void");
        Assert::equals(ctx.module->getNamedValue("exit"), asFuncCall->getCalledFunction(), t+"C3 is a call to exit");
        Assert::equals(1, asFuncCall->getNumArgOperands(), t+"C4 call to exit has one argument");
        Assert::equals(command1, asFuncCall->getArgOperand(0), t+"C5 the argument is the return value from main");

        iterator++;
        auto command3 = &(*iterator);
        Assert::that(llvm::ReturnInst::classof(command3), t+"D1 third command a return statement");
        Assert::llvmIntConstant(static_cast<llvm::ReturnInst*>(command3)->getReturnValue(), 32, 0, t+"D2 the function returns 0");
    }
    //endregion


    public: static void runAll() {
      Assert::warnNotTested("EulProgramTest.initGlobals");
      Assert::warnNotTested("EulProgramTest.emmitObjCode");
      Assert::warnNotTested("EulProgramTest.emmitIRAssembly");

      getAndCreateTest("EulProgramTest.getAndCreate ");
      nextPendingSourceTest("EulProgramTest.nextPendingSourceTest ");
      getEntryPointTest("EulProgramTest.getEntryPointTest ");
      globalsInitTest("EulProgramTest.globalsInitTest ");
      resetTest("EulProgramTest.resetTest ");

      //code gen tests
      declareClibSymbolsTest("EulProgramCodegenTest.declareClibSymbolsTest ");
      makeMainTest("EulProgramCodegenTest.makeMainTest "); //TODO new addition: unit test return value!!
      makeEntryPoint("EulProgramCodegenTest.makeEntryPoint ");
    }
};
