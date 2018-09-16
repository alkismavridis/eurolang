#pragma once



class EulOperatorCodeGenTest {
    //region INFIX OPERATOR TESTS
    public: static void leftShiftOperatorInfixTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);


        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.leftShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 1, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 7, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 128, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes.
        result = EUL_OPERATORS.leftShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 1, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 64), 8, true),
            comp.program.nativeTypes.int64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 256, t+"A2");
        Assert::equals(comp.program.nativeTypes.int64Type.get(), resultType.get(), t+"A2 result type");
    }

    public: static void rightShiftOperatorInfixTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.rightShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 32, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 2, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 8, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes
        result = EUL_OPERATORS.rightShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 64, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 3, true),
            comp.program.nativeTypes.int16Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 16, 8, t+"A2");
        Assert::equals(comp.program.nativeTypes.int16Type.get(), resultType.get(), t+"A2 result type");

        //3. Test a case where sign matters (signed)
        result = EUL_OPERATORS.rightShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
            comp.program.nativeTypes.int8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 231, t+"B1 signed right shift"); //this should become 11100111, which is 231
        Assert::equals(comp.program.nativeTypes.int8Type.get(), resultType.get(), t+"B1 result type");

        //4. Test a case where sign matters (signed)
        result = EUL_OPERATORS.rightShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
            comp.program.nativeTypes.uint8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 39, t+"B2 unsigned right shift"); //this should become 00100111, which is 39
        Assert::equals(comp.program.nativeTypes.uint8Type.get(), resultType.get(), t+"B2 result type");
    }


    public: static void plusOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.plusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 1, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 7, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 8, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes.
        result = EUL_OPERATORS.plusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 1, true),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 8, true),
            comp.program.nativeTypes.int16Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 16, 9, t+"A2");
        Assert::equals(comp.program.nativeTypes.uint16Type.get(), resultType.get(), t+"A2 result type");

        //3. Test float addition
        result = EUL_OPERATORS.plusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -1, false),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 4.23),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmFloatConstant(result, 64, 259.23, 0.0001, t+"A3"); //-1 will result to 255, because we treated it as UInt8
        Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"A3 result type");
    }


    public: static void minusOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.minusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 234, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 34, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 200, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes.
        result = EUL_OPERATORS.minusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 50, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 10, true),
            comp.program.nativeTypes.int16Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 16, 40, t+"A2");
        Assert::equals(comp.program.nativeTypes.int16Type.get(), resultType.get(), t+"A2 result type");


        //3. Test float addition
        result = EUL_OPERATORS.minusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -1, false),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 4.23),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmFloatConstant(result, 64, 250.77, 0.0001, t+"A3"); //-1 will result to 255, because we treated it as UInt8
        Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"A3 result type");
    }

    public: static void starOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.starOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 4, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 120, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes.
        result = EUL_OPERATORS.starOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 50, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 10, true),
            comp.program.nativeTypes.int16Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 16, 500, t+"A2");
        Assert::equals(comp.program.nativeTypes.int16Type.get(), resultType.get(), t+"A2 result type");


        //3. Test float addition
        result = EUL_OPERATORS.starOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, false),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.24),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmFloatConstant(result, 64, 32.4, 0.0001, t+"B1");
        Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"B2 result type");
    }

    public: static void slashOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.slashOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 44, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 11, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 4, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes
        result = EUL_OPERATORS.slashOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 64), 3, true),
            comp.program.nativeTypes.int64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 3, t+"A2");
        Assert::equals(comp.program.nativeTypes.int64Type.get(), resultType.get(), t+"A2 result type");

        //3. Test a case where sign matters (signed)
        result = EUL_OPERATORS.slashOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100 (156)
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
            comp.program.nativeTypes.int8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 206, t+"B1 signed integer division"); //signed version of -100/2 gives -50, which is 11001110 (206)
        Assert::equals(comp.program.nativeTypes.int8Type.get(), resultType.get(), t+"B1 result type");

        //4. Test a case where sign matters (unsigned)
        result = EUL_OPERATORS.slashOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100 (156)
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
            comp.program.nativeTypes.uint8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 78, t+"B2 unsigned integer division"); //unsigned version of -100/2 this should become 10011100b / 2, which is 01001110 (78)
        Assert::equals(comp.program.nativeTypes.uint8Type.get(), resultType.get(), t+"B2 result type");


        //5. Test float addition
        result = EUL_OPERATORS.slashOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, false),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmFloatConstant(result, 64, 3.125, 0.001, t+"C1");
        Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"C2 result type");
    }


    public: static void percentOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test same sized operations
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.percentOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 47, true),
            comp.program.nativeTypes.int32Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 11, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 3, t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

        //2. Test different sizes
        result = EUL_OPERATORS.percentOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, true),
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 3, true),
            comp.program.nativeTypes.int16Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 16, 1, t+"A2");
        Assert::equals(comp.program.nativeTypes.int16Type.get(), resultType.get(), t+"A2 result type");

        //3. Test a case where sign matters (signed)
        result = EUL_OPERATORS.percentOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100 (156)
            comp.program.nativeTypes.int8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 6, true),
            comp.program.nativeTypes.int8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 252, t+"B1 signed integer modulus"); //252 is the unsigned form of -4
        Assert::equals(comp.program.nativeTypes.int8Type.get(), resultType.get(), t+"B1 result type");

        //4. Test a case where sign matters (unsigned)
        result = EUL_OPERATORS.percentOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 100, true), //-100 is 10011100 (156)
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -1, true),
            comp.program.nativeTypes.uint8Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 8, 100, t+"B2 unsigned integer modulus"); //unsigned version of -100/2 this should become 10011100b / 2, which is 01001110 (78)
        Assert::equals(comp.program.nativeTypes.uint8Type.get(), resultType.get(), t+"B2 result type");


        //5. Test float addition
        result = EUL_OPERATORS.percentOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, false),
            comp.program.nativeTypes.uint8Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmFloatConstant(result, 64, 0.4, 0.0001, t+"C1");
        Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"C2 result type");
    }
    //endregion



    //region ASSIGNMENT OPERATIONS
     public: static void assignOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Make an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);

        //2. Create a var declaration (Int32), and insert it into the scope
        VarDeclarationStatement tok(yy::EulParser::token::VAR, std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>());
        tok.declarations->push_back(
            std::make_shared<VarDeclaration>(
                std::make_shared<EulIdToken>("myVar", ctx.currentScope),
                nullptr,
                std::make_shared<EulIntToken>(123, 32, false)
            )
        );
        ctx.currentScope->declare(&tok);
        tok.generateStatement(&ctx);

        //3. Assign a new value to it (an Int64)
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.assignOperator.assignInfix(
            ctx.currentScope->get("myVar").get(),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 64), 999, true),
            comp.program.nativeTypes.int64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 999, t+"A1 result of assignment is the right operand");

        auto instruction = &ctx.builder.GetInsertBlock()->back(); //get the last instruction
        Assert::that(llvm::StoreInst::classof(instruction), t+"A1 is store instruction");
        auto asStoreInst = static_cast<llvm::StoreInst*>(instruction);
        Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"A2 produces an Int32");
        Assert::llvmIntConstant(asStoreInst->getValueOperand(), 32, 999, t+"A3");
        Assert::equals(ctx.currentScope->get("myVar")->llvmValue, asStoreInst->getPointerOperand(), t+"A4 value is assigned to myVar");
        Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A5 result type");


        //TODO test multiple assignment expressions like x = y = 10;
    }
    //endregion





    //region LOGICAL TESTS
    public: static void equalsOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test integer equality
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.equalsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.equalsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"B1 negative int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 negative int result type");


        //3. Test float addition
        resultType = nullptr;
        result = EUL_OPERATORS.equalsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"C1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.equalsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"D1 negative float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 negative float result type");
    }


    public: static void notEqualsOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test integer equality
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.notEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"A1 negative int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 negative int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.notEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"B1 positive int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive int result type");


        //3. Test float addition
        resultType = nullptr;
        result = EUL_OPERATORS.notEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 negative float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.notEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive float result type");
    }

    public: static void sameOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test integer equality
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.sameOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.sameOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"B1 negative int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 negative int result type");


        //3. Test float addition
        resultType = nullptr;
        result = EUL_OPERATORS.sameOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"C1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.sameOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"D1 negative float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 negative float result type");
    }


    public: static void notSameOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test integer equality
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.notSameOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"A1 negative int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 negative int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.notSameOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"B1 positive int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive int result type");


        //3. Test float addition
        resultType = nullptr;
        result = EUL_OPERATORS.notSameOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 negative float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.notSameOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float32Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
            comp.program.nativeTypes.float32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive float result type");
    }

    public: static void lessOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test signed integers
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive signed int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive signed int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"B1 negative signed int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive signed int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 55, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative signed int result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive signed int result type (greater)");

        //2. Test unsigned integers
        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 1, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive unsigned int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive unsigned int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"E1 negative unsigned int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"E2 negative unsigned int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"F1 negative unsigned int result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"F2 negative unsigned int result type (greater)");



        //3. Test floats
        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), -6.7),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"G1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"G2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"H1 negative float result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"H2 negative float result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 10.0),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"I1 negative float result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"I2 negative float result type (greater)");
    }

    public: static void lessEqualsOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test signed integers
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive signed int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive signed int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"B1 positive signed int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive signed int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 55, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative signed int result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive signed int result type (greater)");

        //2. Test unsigned integers
        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 1, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive unsigned int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive unsigned int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"E1 positive unsigned int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"E2 positive unsigned int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"F1 negative unsigned int result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"F2 negative unsigned int result type (greater)");



        //3. Test floats
        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), -6.7),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"G1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"G2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"H1 positive float result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"H2 positive float result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.lessEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 10.0),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"I1 negative float result (greater)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"I2 negative float result type (greater)");
    }

    public: static void moreOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test signed integers
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 50, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), -1, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive signed int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive signed int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"B1 negative signed int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 negative signed int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 55, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative signed int result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive signed int result type (less)");

        //2. Test unsigned integers
        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive unsigned int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive unsigned int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"E1 negative unsigned int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"E2 negative unsigned int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 2, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"F1 negative unsigned int result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"F2 negative unsigned int result type (less)");



        //3. Test floats
        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 7.7),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), -11.5),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"G1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"G2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"H1 negative float result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"H2 negative float result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 10.0),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 33.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"I1 negative float result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"I2 negative float result type (less)");
    }


    public: static void moreEqualsOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Test signed integers
        std::shared_ptr<EulType> resultType;
        auto result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 50, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), -1, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"A1 positive signed int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive signed int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"B1 positive signed int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive signed int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true),
            comp.program.nativeTypes.int16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 55, true),
            comp.program.nativeTypes.int32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"C1 negative signed int result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 negative signed int result type (less)");

        //2. Test unsigned integers
        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"D1 positive unsigned int result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive unsigned int result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"E1 positive unsigned int result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"E2 positive unsigned int result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 2, true),
            comp.program.nativeTypes.uint16Type,
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
            comp.program.nativeTypes.uint32Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"F1 negative unsigned int result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"F2 negative unsigned int result type (less)");



        //3. Test floats
        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 7.7),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), -11.5),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"G1 positive float result");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"G2 positive float result type");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 1, t+"H1 positive float result (equals)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"H2 positive float result type (equals)");

        resultType = nullptr;
        result = EUL_OPERATORS.moreEqualsOperator.performInfix(
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 10.0),
            comp.program.nativeTypes.float64Type,
            llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 33.2),
            comp.program.nativeTypes.float64Type,
            &resultType,
            &ctx
        );
        Assert::llvmIntConstant(result, 1, 0, t+"I1 negative float result (less)");
        Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"I2 negative float result type (less)");
    }
    //endregion



    public: static void runAll() {
        //numeric
        leftShiftOperatorInfixTest("EulOperatorCodeGenTest.leftShiftOperatorInfixTest ");
        rightShiftOperatorInfixTest("EulOperatorCodeGenTest.rightShiftOperatorInfixTest ");
        plusOperatorTest("EulOperatorCodeGenTest.plusOperatorTest ");
        minusOperatorTest("EulOperatorCodeGenTest.minusOperatorTest ");
        starOperatorTest("EulOperatorCodeGenTest.starOperatorTest ");
        slashOperatorTest("EulOperatorCodeGenTest.slashOperatorTest ");
        percentOperatorTest("EulOperatorCodeGenTest.percentOperatorTest ");


        //logical and comparisons
        equalsOperatorTest("EulOperatorCodeGenTest.equalsOperatorTest ");
        notEqualsOperatorTest("EulOperatorCodeGenTest.notEqualsOperatorTest ");
        sameOperatorTest("EulOperatorCodeGenTest.sameOperatorTest ");
        notSameOperatorTest("EulOperatorCodeGenTest.notSameOperatorTest ");

        lessOperatorTest("EulOperatorCodeGenTest.lessOperatorTest ");
        lessEqualsOperatorTest("EulOperatorCodeGenTest.lessEqualsOperatorTest ");
        moreOperatorTest("EulOperatorCodeGenTest.moreOperatorTest ");
        moreEqualsOperatorTest("EulOperatorCodeGenTest.moreEqualsOperatorTest ");



        //assignments
        assignOperatorTest("EulOperatorCodeGenTest.assignOperatorTest ");
    }
};