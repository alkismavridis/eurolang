#pragma once



class EulProgramCodegenTest {

    public: static void declareClibSymbolsTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope);

        //1. Call the function
        comp.program.declareClibSymbols(&ctx);

        //2. Assert that symbols are inserted into scope, and into the llvm module
        //exit(Int32)
        auto eulSymbol = comp.program.globalScope->getOwnSymbol("exit");
        Assert::notNull(eulSymbol.get(), t+"A1 exit is defined in global scope");
        Assert::equals(yy::EulParser::token::VAL, eulSymbol->changeType, t+"A2 is val");
        Assert::equals(FUNCTION_TYPE, eulSymbol->varType->getTypeEnum(), t+"A3 is function");

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
        Assert::equals(FUNCTION_TYPE, eulSymbol->varType->getTypeEnum(), t+"B3 is function");

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
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope);

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
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope);
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


    public: static void runAll() {
        declareClibSymbolsTest("EulProgramCodegenTest.declareClibSymbolsTest ");
        makeMainTest("EulProgramCodegenTest.makeMainTest ");
        makeEntryPoint("EulProgramCodegenTest.makeEntryPoint ");
    }
};