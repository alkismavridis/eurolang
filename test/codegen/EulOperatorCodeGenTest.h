#pragma once



class EulOperatorCodeGenTest {
    //region UTILS
    public: static void doCommonIntMergingTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        auto& nativeTypes = comp.program.nativeTypes;

        //1. Check size behaviour (bigger one is returned, unsigned wins)
        auto result = EulOperator::doCommonIntMerging(nativeTypes.int32Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A1 same types return itself.");

        result = EulOperator::doCommonIntMerging(nativeTypes.int16Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A2 bigger type is returned");

        result = EulOperator::doCommonIntMerging(nativeTypes.uint32Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A3 unsigned wins");

        result = EulOperator::doCommonIntMerging(nativeTypes.uint16Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A4 unsigned and bigger wins");

        result = EulOperator::doCommonIntMerging(nativeTypes.int8Type, nativeTypes.int16Type, &ctx);
        Assert::equals(nativeTypes.int16Type.get(), result.get(), t+"A5 bigger type is returned.");


        //2. Fail case: test invalid int sizes
        try {
            EulOperator::doCommonIntMerging(std::make_shared<EulIntegerType>(67, false), nativeTypes.int32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid int size, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Wrong int size: 67", e.message, t+"B2");
        }


        //3. Fail case: test non integer types
        try {
            EulOperator::doCommonIntMerging(nativeTypes.stringType, nativeTypes.int32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to int, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Int type expected.", e.message, t+"C2");
        }
    }
    //endregion


    //region INFIX OPERATOR TESTS
    public: static void leftShiftOperatorInfixTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test same sized operations
        auto result = EUL_OPERATORS.leftShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 1, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 7, true),
            comp.program.nativeTypes.int32Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 128, t+"A1");

        //2. Test different sizes.
        result = EUL_OPERATORS.leftShiftOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 1, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 8, true),
            comp.program.nativeTypes.int64Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 256, t+"A2");
    }


    public: static void plusOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test same sized operations
        auto result = EUL_OPERATORS.plusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 1, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 7, true),
            comp.program.nativeTypes.int32Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 8, t+"A1");

        //2. Test different sizes.
        result = EUL_OPERATORS.plusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 1, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 8, true),
            comp.program.nativeTypes.int64Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 9, t+"A2");
    }


    public: static void minusOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test same sized operations
        auto result = EUL_OPERATORS.minusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 234, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 34, true),
            comp.program.nativeTypes.int32Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 200, t+"A1");

        //2. Test different sizes.
        result = EUL_OPERATORS.minusOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 50, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 10, true),
            comp.program.nativeTypes.int64Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 40, t+"A2");
    }

    public: static void startOperatorTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test same sized operations
        auto result = EUL_OPERATORS.starOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 4, true),
            comp.program.nativeTypes.int32Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 32, 120, t+"A1");

        //2. Test different sizes.
        result = EUL_OPERATORS.starOperator.performInfix(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 50, true),
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 10, true),
            comp.program.nativeTypes.int64Type,
            &ctx
        );
        Assert::llvmIntConstant(result, 64, 500, t+"A2");
    }
    //endregion


    public: static void runAll() {
        doCommonIntMergingTest("EulOperatorCodeGenTest.doCommonIntMergingTest ");

        leftShiftOperatorInfixTest("EulOperatorCodeGenTest.leftShiftOperatorInfixTest ");
        plusOperatorTest("EulOperatorCodeGenTest.plusOperatorTest ");
        minusOperatorTest("EulOperatorCodeGenTest.minusOperatorTest ");
        startOperatorTest("EulOperatorCodeGenTest.startOperatorTest ");
    }
};