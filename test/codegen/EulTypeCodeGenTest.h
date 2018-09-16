#pragma once



class EulTypeCodeGenTest {

    //region TYPE CASTINGS
    public: static void doCommonIntMergingTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        auto& nativeTypes = comp.program.nativeTypes;

        //1. Check size behaviour (bigger one is returned, unsigned wins)
        auto result = EulType::doCommonIntMerging(nativeTypes.int32Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A1 same types return itself.");

        result = EulType::doCommonIntMerging(nativeTypes.int16Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A2 bigger type is returned");

        result = EulType::doCommonIntMerging(nativeTypes.uint32Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A3 unsigned wins");

        result = EulType::doCommonIntMerging(nativeTypes.uint16Type, nativeTypes.int32Type, &ctx);
        Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A4 unsigned and bigger wins");

        result = EulType::doCommonIntMerging(nativeTypes.int8Type, nativeTypes.int16Type, &ctx);
        Assert::equals(nativeTypes.int16Type.get(), result.get(), t+"A5 bigger type is returned.");


        //2. Fail case: test invalid int sizes
        try {
            EulType::doCommonIntMerging(std::make_shared<EulIntegerType>(67, false), nativeTypes.int32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid int size, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Wrong int size: 67", e.message, t+"B2");
        }


        //3. Fail case: test non integer types
        try {
            EulType::doCommonIntMerging(nativeTypes.stringType, nativeTypes.int32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to int, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Invalid conversion to int.", e.message, t+"C2");
        }
    }

    public: static void doCommonFloatMergingTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        auto& nativeTypes = comp.program.nativeTypes;

        //1. Check size behaviour (bigger one is returned)
        auto result = EulType::doCommonFloatMerging(nativeTypes.float32Type, nativeTypes.float32Type, &ctx);
        Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"A1 same types return itself.");

        result = EulType::doCommonFloatMerging(nativeTypes.float64Type, nativeTypes.float64Type, &ctx);
        Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A2 same types return itself.");

        result = EulType::doCommonFloatMerging(nativeTypes.float64Type, nativeTypes.float32Type, &ctx);
        Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A3 same types return itself.");

        result = EulType::doCommonFloatMerging(nativeTypes.float32Type, nativeTypes.float64Type, &ctx);
        Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A4 same types return itself.");


        //2. Fail case: test invalid int sizes
        try {
            EulType::doCommonFloatMerging(std::make_shared<EulFloatType>(67), nativeTypes.float64Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid float size, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Wrong float size: 67", e.message, t+"B2");
        }

        //3. Test non float input parameter
        try {
            EulType::doCommonFloatMerging(nativeTypes.stringType, nativeTypes.float32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Invalid conversion to float.", e.message, t+"C2");
        }
    }

    public: static void doCommonNumberMergingTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        auto& nativeTypes = comp.program.nativeTypes;


        //1.test both int
        auto result = EulType::doCommonNumberMerging(nativeTypes.int32Type, nativeTypes.int8Type, &ctx);
        Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A1 both integers");

        //2.test left float and right int right
        result = EulType::doCommonNumberMerging(nativeTypes.float32Type, nativeTypes.int8Type, &ctx);
        Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"B1 left float, right integer");

        //3.test right float and left int
        result = EulType::doCommonNumberMerging(nativeTypes.int8Type, nativeTypes.float32Type, &ctx);
        Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"B2 right float, left integer");

        //4. test both floats
        result = EulType::doCommonNumberMerging(nativeTypes.float64Type, nativeTypes.float32Type, &ctx);
        Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"C1 right float, left integer");

        //5. test other type
        try {
            EulType::doCommonNumberMerging(nativeTypes.stringType, nativeTypes.float32Type, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"D1");
            Assert::equals("Invalid conversion to number.", e.message, t+"D2");
        }

        try {
            EulType::doCommonNumberMerging(nativeTypes.float32Type, nativeTypes.stringType, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"E1");
            Assert::equals("Invalid conversion to number.", e.message, t+"E2");
        }

        try {
            EulType::doCommonNumberMerging(nativeTypes.int32Type, nativeTypes.stringType, &ctx);
            Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"F1");
            Assert::equals("Invalid conversion to number.", e.message, t+"F2");
        }
    }
    //endregion



    //region VALUE CASTINGS
    public: static void castToIntegerTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Cast an Int8 to Int32
        auto valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, false));
        auto convertedValue = comp.program.nativeTypes.int32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.int8Type.get(),
            false,
            &ctx
        );
        Assert::llvmIntConstant(convertedValue, 32, 4294967295, t+"A1"); //4294967295 is -1 in unsigned integer form.

        //2. Cast an Int8 to UInt32
        valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, false));
        convertedValue = comp.program.nativeTypes.uint32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.int8Type.get(),
            false,
            &ctx
        );
        Assert::llvmIntConstant(convertedValue, 32, 255, t+"B1"); //255 is -1 in unsigned char form, which is the case because we perform zero extension.

        //3. Try to cast something other than integer. This should fail
        try {
            comp.program.nativeTypes.uint32Type->castValue(
                valueToConvert,
                comp.program.nativeTypes.stringType.get(),
                false,
                &ctx
            );
            Assert::fail(t+"Exception expected due to converting a non integer type to integer, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(NOT_IMPLEMENTED, e.type, t+"C1");
            Assert::equals("NOT_IMPLEMENTED only ints can be casted to ints.", e.message, t+"C2");
        }
    }

    public: static void castIntToFloatValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Cast a signed Int to Float
        auto valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, true));
        auto convertedValue = comp.program.nativeTypes.float32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.int8Type.get(),
            false,
            &ctx
        );
        Assert::llvmFloatConstant(convertedValue, 32, -1.0, 0.000001, t+"A1 unsigned int to float");


        //2. Cast a unsigned Int to Float
        valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(16, -2, true));
        convertedValue = comp.program.nativeTypes.float32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.uint16Type.get(),
            false,
            &ctx
        );
        Assert::llvmFloatConstant(convertedValue, 32, 65534, 0.000001, t+"A2 signed int to float"); //65534 is -2 in 16bit unsigned integer form
    }

    public: static void castFloatToFloatValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

        //1. Cast a equal types
        auto valueToConvert = llvm::ConstantFP::get(llvm::Type::getFloatTy(ctx.context), 99.543);
        auto convertedValue = comp.program.nativeTypes.float32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.float32Type.get(),
            false,
            &ctx
        );
        Assert::equals(valueToConvert, convertedValue, t+"A1 cast float32 to float32 should not do any cast");

        valueToConvert = llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 12345.678);
        convertedValue = comp.program.nativeTypes.float64Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.float64Type.get(),
            false,
            &ctx
        );
        Assert::equals(valueToConvert, convertedValue, t+"A2 cast float64 to float64 should not do any cast");


        //2. Cast a float to double, and a double to float
        valueToConvert = llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 123.4);
        convertedValue = comp.program.nativeTypes.float32Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.float64Type.get(),
            false,
            &ctx
        );
        Assert::llvmFloatConstant(convertedValue, 32, 123.4, 0.001, t+"B1 cast float64 to float32");

        valueToConvert = llvm::ConstantFP::get(llvm::Type::getFloatTy(ctx.context), 123.4);
        convertedValue = comp.program.nativeTypes.float64Type->castValue(
            valueToConvert,
            comp.program.nativeTypes.float32Type.get(),
            false,
            &ctx
        );
        Assert::llvmFloatConstant(convertedValue, 64, 123.4, 0.001, t+"B2 cast float32 to float64");
    }
    //endregion



    public: static void runAll() {
        doCommonIntMergingTest("EulTypeCodeGenTest.doCommonIntMergingTest ");
        doCommonFloatMergingTest("EulTypeCodeGenTest.doCommonFloatMergingTest ");
        doCommonNumberMergingTest("EulTypeCodeGenTest.doCommonNumberMerging ");

        castToIntegerTest("EulTypeCodeGenTest.castToIntegerTest ");


        castIntToFloatValueTest("EulTypeCodeGenTest.castIntToFloatValueTest ");
        castFloatToFloatValueTest("EulTypeCodeGenTest.castFloatToFloatValueTest ");
       // castValueTest("EulTypeCodeGenTest.castToIntegerTest ");



    }
};