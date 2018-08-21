#pragma once



class EulCodeGenContextTest {
    //region GLOBAL VARIABLE GENERATION
    public: static void makeGlobalLiteralTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create literals and check the results
        // NOTE: produced type is always the same as the input type, put with an extra pointer.
        auto glob1 = ctx.makeGlobalLiteral(comp.program.nativeTypes.int32Type->getLlvmType(&ctx));
        Assert::equals(".glob1", glob1->getName(), t+"A1");
        Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx)->getPointerTo(), glob1->getType(), t+"A2");

        auto glob2 = ctx.makeGlobalLiteral(comp.program.nativeTypes.stringType->getLlvmType(&ctx));
        Assert::equals(".glob2", glob2->getName(), t+"B1");
        Assert::equals(comp.program.nativeTypes.stringType->getLlvmType(&ctx)->getPointerTo(), glob2->getType(), t+"B2");

        auto glob3 = ctx.makeGlobalLiteral(comp.program.nativeTypes.char32Type->getLlvmType(&ctx)->getPointerTo());
        Assert::equals(".glob3", glob3->getName(), t+"C1");
        Assert::equals(comp.program.nativeTypes.char32Type->getLlvmType(&ctx)->getPointerTo()->getPointerTo(), glob3->getType(), t+"C2");
    }
    //endregion



    //region TYPE CASTINGS
    public: static void castToIntegerTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Cast an Int8 to Int32
        auto valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, false));
        auto targetEulType = comp.program.nativeTypes.int32Type;
        auto convertedValue = ctx.castToInteger(
            valueToConvert,
            static_cast<llvm::IntegerType*>(targetEulType->getLlvmType(&ctx)),
            static_cast<EulIntegerType*>(targetEulType.get())
        );
        Assert::llvmIntConstant(convertedValue, 32, 4294967295, t+"A1"); //4294967295 is -1 in unsigned integer form.

        //2. Cast an Int8 to UInt32
        valueToConvert = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, false));
        targetEulType = comp.program.nativeTypes.uint32Type;
        convertedValue = ctx.castToInteger(
             valueToConvert,
             static_cast<llvm::IntegerType*>(targetEulType->getLlvmType(&ctx)),
             static_cast<EulIntegerType*>(targetEulType.get())
        );
        Assert::llvmIntConstant(convertedValue, 32, 255, t+"B1"); //255 is -1 in unsigned char form, which is the case because we perform zero extension.

        //3. Try to cast something other than integer. THis sould fail
        try {
            ctx.castToInteger(
                 llvm::ConstantFP::get(comp.program.nativeTypes.stringType->getLlvmType(&ctx), 12.6),
                 static_cast<llvm::IntegerType*>(targetEulType->getLlvmType(&ctx)),
                 static_cast<EulIntegerType*>(targetEulType.get())
            );
            Assert::fail(t+"Exception expected due to converting a non integer type to integer, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(NOT_IMPLEMENTED, e.type, t+"C1");
            Assert::equals("NOT_IMPLEMENTED only ints can be casted to ints.", e.message, t+"C2");
        }
    }


    public: static void castValueTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Test proper void - no-value treatment
        auto castedValue = ctx.castValue(nullptr, llvm::Type::getVoidTy(ctx.context), nullptr); //no value, void type. This should successfully return null.
        Assert::null(castedValue, t+"A1");

        //try to cast a value to void.
        try {
            ctx.castValue(llvm::ConstantInt::get(ctx.context, llvm::APInt(8, -1, false)), llvm::Type::getVoidTy(ctx.context), nullptr);
            Assert::fail(t+" Expected exception due to conversion attempt from a value to void, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"A2");
            Assert::equals("Void expected, but TODO_typeName was found.", e.message, t+"A3");
        }

        try {
            ctx.castValue(nullptr, llvm::Type::getInt32Ty(ctx.context), comp.program.nativeTypes.int32Type.get());
            Assert::fail(t+" Expected exception due to conversion attempt from a null value to a non void type, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"A4");
            Assert::equals("TODO_type value required, but void was found.", e.message, t+"A5");
        }


        //2. Try converting a variable to its own type. The variable itself should be returned.
        auto valueToCast = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, 55, false));
        castedValue = ctx.castValue(valueToCast, llvm::Type::getInt8Ty(ctx.context), comp.program.nativeTypes.int8Type.get());
        Assert::that(castedValue == valueToCast, t+"B1");

        //3. Cast an integer to a different int type
        castedValue = ctx.castValue(valueToCast, llvm::Type::getInt32Ty(ctx.context), comp.program.nativeTypes.int32Type.get());
        Assert::llvmIntConstant(castedValue, 32, 55, t+"C1");

        //4. Cast incompatible types.
        try {
            valueToCast = llvm::ConstantInt::get(ctx.context, llvm::APInt(8, 55, false));
            ctx.castValue(valueToCast, llvm::Type::getInt32Ty(ctx.context)->getPointerTo(), comp.program.nativeTypes.int32Type->getPointerTo().get());
            Assert::fail(t+" Expected exception due to incompatible types conversion attempt, but none was thrown.");
        }
        catch (EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"D1");
            Assert::equals("Inconsistent type conversion.", e.message, t+"D2");
        }
    }
    //endregion


    public: static void runAll() {
        makeGlobalLiteralTest("EulCodeGenContextTest.makeGlobalLiteralTest ");

        castToIntegerTest("EulCodeGenContextTest.castToIntegerTest ");
        castValueTest("EulCodeGenContextTest.castValueTest ");
    }
};