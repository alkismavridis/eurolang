#pragma once



class EulAstCodeGenTest {

    //region DECLARATION AST TESTS
    public: static void varDeclarationGetEulTypeTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a var declaration
        VarDeclaration tok(
            std::make_shared<EulIdToken>("hello", ctx.currentScope),
            comp.program.nativeTypes.float32Type,           //the symbol has type Float32, but its value is a Float64 literal
            std::make_shared<EulFloatToken>(7.5, 64)
        );

        //2. Get its eul type when both declared type and value are present. The declared type must be returned
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A1");

        //3. Try a declaration without a defined type. The values type should be returned
        tok.varType = nullptr;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.float64Type.get(), t+"A2");


        //3. Try a declaration without any of the two. An exception should be thrown.
        try {
            tok.value = nullptr;
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+"Exception expected due to var declaration with that lacks both type and value. But none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(NOT_IMPLEMENTED, e.type, t+"A3");
            Assert::equals("NOT IMPLEMENTED: variable without initial value.", e.message, t+"A4");
        }
    }
    //endregion


    //region STATEMENT TESTS
    public: static void varDeclarationStatementValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);

        //2. Create a var declaration with two variables: one will have a value, the second not.
        VarDeclarationStatement tok(yy::EulParser::token::VAR, std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>());

        tok.declarations->push_back(
            std::make_shared<VarDeclaration>(
                std::make_shared<EulIdToken>("first", ctx.currentScope),
                nullptr,
                std::make_shared<EulIntToken>(123, 32, false)
            )
        );
        tok.declarations->push_back(
            std::make_shared<VarDeclaration>(
                std::make_shared<EulIdToken>("second", ctx.currentScope),
                comp.program.nativeTypes.float64Type,
                nullptr
            )
        );

        //declare them into the scope, too (important)
        ctx.currentScope->declare(&tok);

        //3. Generate the statement
        tok.generateStatement(&ctx);


        //4. Assert the resulted instructions
        Assert::equals(4, ctx.builder.GetInsertBlock()->size(), t+"A1");

        //4a. alloca instruction for first
        auto it = ctx.builder.GetInsertBlock()->begin();
        llvm::Instruction* instruction = &(*it);
        Assert::that(llvm::AllocaInst::classof(instruction), t+"B1");
        auto asAllocaInst = static_cast<llvm::AllocaInst*>(instruction);
        Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asAllocaInst->getAllocatedType(), t+"B2");

        //4b. store instruction for first
        it++;
        instruction = &(*it);
        Assert::that(llvm::StoreInst::classof(instruction), t+"C1");
        auto asStoreInst = static_cast<llvm::StoreInst*>(instruction);
        Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"C2");
        Assert::llvmIntConstant(asStoreInst->getValueOperand(), 32, 123, t+"C3");
        Assert::equals(asAllocaInst, asStoreInst->getPointerOperand(), t+"C4");

        //4c. alloca instruction for second
        it++;
        instruction = &(*it);
        Assert::that(llvm::AllocaInst::classof(instruction), t+"D1");
        asAllocaInst = static_cast<llvm::AllocaInst*>(instruction);
        Assert::equals(comp.program.nativeTypes.float64Type->getLlvmType(&ctx), asAllocaInst->getAllocatedType(), t+"D2");

        //4d. store instruction for second
        it++;
        instruction = &(*it);
        Assert::that(llvm::StoreInst::classof(instruction), t+"E1");
        asStoreInst = static_cast<llvm::StoreInst*>(instruction);
        Assert::equals(comp.program.nativeTypes.float64Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"E2");
        Assert::that(llvm::UndefValue::classof(asStoreInst->getValueOperand()), t+"E3");
        Assert::equals(asAllocaInst, asStoreInst->getPointerOperand(), t+"E4");

        //5. Check that unreachable statements are not allowed
        ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
        try {
            tok.generateStatement(&ctx);
            Assert::fail(t+"Exception expected due to unreachable expression statement, But none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"F1");
            Assert::equals("Unreachable statement.", e.message, t+"F2");
        }
    }


    public: static void eulExpStatementValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);
        comp.program.declareClibSymbols(&ctx);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);


        //2. Create an operation (like a binary one), and insert it into an EulExpStatement
        auto funcCallExp = std::make_shared<EulFunctionCallExp>(
            std::make_shared<EulIdToken>("exit", ctx.currentScope),
            std::make_shared<std::vector<std::shared_ptr<EulToken>>>()
        );
        funcCallExp->params->push_back(std::make_shared<EulIntToken>(123,32,false));
        EulExpStatement tok(funcCallExp);

        //3. Execute the expression and check result
        tok.generateStatement(&ctx);
        Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"A1");


        //4. Check that unreachable statements are not allowed
        ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
        try {
            tok.generateStatement(&ctx);
            Assert::fail(t+"Exception expected due to unreachable expression statement, But none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"A2");
            Assert::equals("Unreachable statement.", e.message, t+"A3");
        }
    }

    public: static void eulReturnStatementValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);
        comp.program.declareClibSymbols(&ctx);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);


        //2. Create an operation (like a binary one), and insert it into an EulExpStatement
        ReturnStatement tok(std::make_shared<EulIntToken>(123,32,false));

        //3. Execute the expression and check result
        tok.generateStatement(&ctx);
        Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"A1");

        auto instruction = &(*ctx.builder.GetInsertBlock()->begin());
        Assert::that(llvm::ReturnInst::classof(instruction), t+"A2");

        auto asRetInst = static_cast<llvm::ReturnInst*>(instruction);
        Assert::llvmIntConstant(asRetInst->getReturnValue(), 32, 123, t+"A3");


        //4. Check that unreachable statements are not allowed
        ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
        try {
            tok.generateStatement(&ctx);
            Assert::fail(t+"Exception expected due to unreachable expression statement, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Unreachable statement.", e.message, t+"B2");
        }
    }
    //endregion



    //region EXPRESSION TESTS
     public: static void eulFunctionCallExpValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);
        comp.program.declareClibSymbols(&ctx);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);


        //2. Setup a call expression
        EulFunctionCallExp tok(
            std::make_shared<EulIdToken>("exit", ctx.currentScope),
            std::make_shared<std::vector<std::shared_ptr<EulToken>>>()
        );
        tok.params->push_back(std::make_shared<EulIntToken>(123,32,false));

        //3. Run it and check the result
        auto val = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::that(val->getType()->isVoidTy(), t+"A1");

        Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"B1");
        auto instruction = &(*ctx.builder.GetInsertBlock()->begin());
        Assert::that(llvm::CallInst::classof(instruction), t+"B2");

        auto asCallInst = static_cast<llvm::CallInst*>(instruction);
        Assert::that(asCallInst->getType()->isVoidTy(), t+"C1");
        Assert::equals(ctx.currentScope->get("exit")->llvmValue, asCallInst->getCalledFunction(), t+"C2");
        Assert::equals(1, asCallInst->getNumArgOperands(), t+"C3");
        Assert::llvmIntConstant(asCallInst->getArgOperand(0), 32, 123, t+"C4");


        //4. Test error cases: wrong argument list count
        tok.params->push_back(std::make_shared<EulIntToken>(123,32,false));
        try {
            tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Exception expected due to wrong argument list count, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(NOT_IMPLEMENTED, e.type, t+"D1");
            Assert::equals("NOT_IMPLEMENTED wrong parameter list count.", e.message, t+"D2");
        }
    }


    public: static void eulInfixExpValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);

        //2. Create an infix expression
        EulInfixExp tok(
            std::make_shared<EulIntToken>(123, 32, false),
            &EUL_OPERATORS.plusOperator,
            std::make_shared<EulIntToken>(153, 64, false)
        );

        //3. Run in and see the result
        auto value = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(value, 64, 276, t+"A1");
    }
    //endregion



    //region TYPE TESTS
    public: static void primitiveTypesTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test a couple of ints
        Assert::equals(llvm::IntegerType::get(ctx.context, 8), comp.program.nativeTypes.int8Type->getLlvmType(&ctx), t+"A1");
        Assert::equals(llvm::IntegerType::get(ctx.context, 32), comp.program.nativeTypes.uint32Type->getLlvmType(&ctx), t+"A2");

        //2. Test a couple of chars
        Assert::equals(llvm::IntegerType::get(ctx.context, 8), comp.program.nativeTypes.char8Type->getLlvmType(&ctx), t+"B1");
        Assert::equals(llvm::IntegerType::get(ctx.context, 32), comp.program.nativeTypes.char32Type->getLlvmType(&ctx), t+"B2");

        //3. Test a couple of floats
        Assert::equals(llvm::Type::getFloatTy(ctx.context), comp.program.nativeTypes.float32Type->getLlvmType(&ctx), t+"C1");
        Assert::equals(llvm::Type::getDoubleTy(ctx.context), comp.program.nativeTypes.float64Type->getLlvmType(&ctx), t+"C2");
        try {
            EulFloatType wrongType(35);
            wrongType.getLlvmType(&ctx);
            Assert::fail(t+" Exception expected due to wrong float type size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C3");
            Assert::equals("Invalid floating point size: 35. Please use one of 32, 64.", e.message, t+"C4");
        }

        //4. String type
        Assert::equals(llvm::IntegerType::get(ctx.context, 8)->getPointerTo(), comp.program.nativeTypes.stringType->getLlvmType(&ctx), t+"D1");
    }

    public: static void pointerTypeTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);


        //1. Create a pointer
        EulPointerType ptrType(comp.program.nativeTypes.float32Type.get(), 3);
        auto expected = llvm::Type::getFloatTy(ctx.context)
            ->getPointerTo()
            ->getPointerTo()
            ->getPointerTo();

        Assert::equals(expected, ptrType.getLlvmType(&ctx), t+"A1");
    }

    public: static void namedTypeTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);


        //1. Define a named type
        auto namedLlvmType = llvm::StructType::create(ctx.context, "MyCoolType");
        namedLlvmType->setBody(llvm::ArrayRef<llvm::Type*>(
            llvm::IntegerType::get(ctx.context, 8)->getPointerTo()
        ));


        //2. Create a Named type and try accessing llvm type. It should fetched exactly namedLlvmType
        EulNamedType namedEulType("MyCoolType");
        auto fetched = namedEulType.getLlvmType(&ctx);
        Assert::equals(namedLlvmType, fetched, t+"A1");
    }


    public: static void functionTypeTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);


        //1. Create an eul function type with return type and parameters
        auto eulType = EulFunctionType(comp.program.nativeTypes.stringType);
        eulType.argTypes.push_back(comp.program.nativeTypes.int32Type);
        eulType.argTypes.push_back(comp.program.nativeTypes.int64Type);
        auto llvmType = eulType.getLlvmType(&ctx);

        //2. Assert result.
        Assert::that(llvm::FunctionType::classof(llvmType), t+"A1");
        auto asFunc = static_cast<llvm::FunctionType*>(llvmType);

        Assert::equals(comp.program.nativeTypes.stringType->getLlvmType(&ctx), asFunc->getReturnType(), t+"A2");
        Assert::equals(2, asFunc->getNumParams(), t+"A3");
        Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asFunc->getParamType(0), t+"A4");
        Assert::equals(comp.program.nativeTypes.int64Type->getLlvmType(&ctx), asFunc->getParamType(1), t+"A5");

        //3. Build a function without parameters and no return type
        auto eulType2 = EulFunctionType(nullptr);
        llvmType = eulType2.getLlvmType(&ctx);

        //4. Check result
        Assert::that(llvm::FunctionType::classof(llvmType), t+"B1");
        asFunc = static_cast<llvm::FunctionType*>(llvmType);
        Assert::that(asFunc->getReturnType()->isVoidTy(), t+"B2");
        Assert::equals(0, asFunc->getNumParams(), t+"B3");
    }
    //endregion






    public: static void runAll() {
        varDeclarationGetEulTypeTest("EulAstCodeGenTest.varDeclarationGetEulTypeTest ");

        varDeclarationStatementValueTest("EulAstCodeGenTest.varDeclarationStatementValueTest ");
        eulExpStatementValueTest("EulAstCodeGenTest.eulExpStatementValueTest ");
        eulReturnStatementValueTest("EulAstCodeGenTest.eulReturnStatementValueTest ");

        eulFunctionCallExpValueTest("EulAstCodeGenTest.eulFunctionCallExpValueTest ");
        eulInfixExpValueTest("EulAstCodeGenTest.eulInfixExpValueTest ");


        primitiveTypesTest("EulAstCodeGenTest.primitiveTypesTest ");
        namedTypeTest("EulAstCodeGenTest.namedTypeTest ");
        pointerTypeTest("EulAstCodeGenTest.pointerTypeTest ");
        functionTypeTest("EulAstCodeGenTest.functionTypeTest ");
    }
};