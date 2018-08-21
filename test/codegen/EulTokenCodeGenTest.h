#pragma once

class EulTokenCodeGenTest {
    //region CHAR TESTS
    public: static void generateCharValue(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulCharToken tok('b', 8);
        auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 8, (int)'b', t+"A1");

        //2. Test various sizes and values
        tok.size = 16;
        tok.value = 0xcf8e; //greek ώ
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 16, 0xcf8e, t+"A2");

        tok.size = 32;
        tok.value = 0xf0a09c8e; //chinese 𠜎
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 32, 0xf0a09c8e, t+"A3");

        //3. Test an invalid size
        tok.size = 64;
        try {
            llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Invalid character size: 64. Please use one of 8, 16, 32.", e.message, t+"B2");
        }
    }


    public: static void generateCharEulType(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulCharToken tok('b', 8);
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.char8Type.get(), t+"A1");

        //2. Test various sizes and values
        tok.size = 16;
        tok.value = 0xcf8e; //greek ώ
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.char16Type.get(), t+"A2");

        tok.size = 32;
        tok.value = 0xf0a09c8e; //chinese 𠜎
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.char32Type.get(), t+"A3");

        //3. Test an invalid size
        tok.size = 64;
        try {
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Invalid character size: 64. Please use one of 8, 16, 32.", e.message, t+"B2");
        }
    }
    //endregion




    //region FLOAT TESTS
    public: static void generateFloatValue(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulFloatToken tok(12.5, 32);
        auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmFloatConstant(llvmValue, 32, 12.5, 0.001, t+"A1");

        //2. Test various sizes and values
        tok.size = 64;
        tok.value = 123.7;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmFloatConstant(llvmValue, 64, 123.7, 0.001, t+"A2");

        //3. Test an invalid size
        tok.size = 14;
        try {
            llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Invalid floating point size: 14. Please use one of 32, 64.", e.message, t+"B2");
        }
    }


    public: static void generateFloatEulType(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulFloatToken tok(12.5, 32);
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A1");

        //2. Test various sizes and values
        tok.size = 64;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.float64Type.get(), t+"A2");

        //3. Test an invalid size
        tok.size = 14;
        try {
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"B1");
            Assert::equals("Invalid floating point size: 14. Please use one of 32, 64.", e.message, t+"B2");
        }
    }
    //endregion



    //region INT TESTS
    public: static void generateIntValue(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulIntToken tok(123, 8, false);
        auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 8, 123, t+"A1");

        //2. Test various sizes and values (signed)
        tok.size = 16;
        tok.value = 456;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 16, 456, t+"A2");

        tok.size = 32;
        tok.value = 52767;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 32, 52767, t+"A3");

        tok.size = 64;
        tok.value = 3147483647;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 64, 3147483647, t+"A4");


        //3. Test various sizes and values (unsigned)
        tok.isUnsigned = true;
        tok.size = 8;
        tok.value = 200;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 8, 200, t+"B1");

        tok.size = 16;
        tok.value = 456;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 16, 456, t+"B2");

        tok.size = 32;
        tok.value = 69535;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 32, 69535, t+"B3");

        tok.size = 64;
        tok.value = 7294967295;
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmIntConstant(llvmValue, 64, 7294967295, t+"B4");

        //4. Test an invalid size (both signed and unsigned)
        tok.size = 33;
        tok.isUnsigned = false;
        try {
            llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"C2");
        }

        tok.size = 33;
        tok.isUnsigned = true;
        try {
            llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"D1");
            Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"D2");
        }
    }


    public: static void generateIntEulType(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a char token and get its llvm value
        EulIntToken tok(123, 8, false);
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.int8Type.get(), t+"A1");

        //2. Test various sizes and values (signed)
        tok.size = 16;
        tok.value = 456;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.int16Type.get(), t+"A2");

        tok.size = 32;
        tok.value = 52767;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.int32Type.get(), t+"A3");

        tok.size = 64;
        tok.value = 3147483647;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.int64Type.get(), t+"A4");


        //3. Test various sizes and values (unsigned)
        tok.isUnsigned = true;
        tok.size = 8;
        tok.value = 200;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.uint8Type.get(), t+"B1");

        tok.size = 16;
        tok.value = 456;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.uint16Type.get(), t+"B2");

        tok.size = 32;
        tok.value = 69535;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.uint32Type.get(), t+"B3");

        tok.size = 64;
        tok.value = 7294967295;
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.uint64Type.get(), t+"B4");

        //4. Test an invalid size (both signed and unsigned)
        tok.size = 33;
        tok.isUnsigned = false;
        try {
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"C2");
        }

        tok.size = 33;
        tok.isUnsigned = true;
        try {
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"D1");
            Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"D2");
        }
    }
    //endregion



    //region STRING TESTS
    public: static void generateStringValue(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a string and get its value
        EulStringToken tok("hello\n");
        auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmStringConstant(llvmValue, "hello\n", &ctx, t+"A1");

        //2. Create a string and get its value
        EulStringToken tok2("one_two\n");
        llvmValue = tok2.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmStringConstant(llvmValue, "one_two\n", &ctx, t+"A2");

    }

    public: static void generateStringEulType(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Create a string token and check its type
        EulStringToken tok("hello\n");
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.stringType.get(), t+"A1");
    }
    //endregion





    //region ID TESTS
     public: static void generateIdEulType(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Declare a couple of symbols
        comp.program.globalScope.declare(
            "new1",
            std::make_shared<EulSymbol>(
                yy::EulParser::token::VAR,
                comp.program.nativeTypes.stringType,
                std::make_shared<EulStringToken>("123")
            )
        );
        comp.program.globalScope.declare(
            "new2",
            std::make_shared<EulSymbol>(
                yy::EulParser::token::VAR,
                comp.program.nativeTypes.float32Type,
                std::make_shared<EulFloatToken>(2.3, 32)
            )
        );

        //2. Get the type of the symbols
        EulIdToken tok("new1", &comp.program.globalScope);
        auto eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.stringType.get(), t+"A1");

        tok.name.assign("new2");
        eulType = tok.getEulType(&ctx, 0);
        Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A2");

        tok.name.assign("Int32");
        eulType = tok.getEulType(&ctx, 0);
        Assert::null(eulType.get(), t+"B1");


        //3. Try accessing a non existing symbol
        try {
            tok.name.assign("iDoNotExist");
            eulType = tok.getEulType(&ctx, 0);
            Assert::fail(t+" Expected exception due to non existing symbol, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"C1");
            Assert::equals("iDoNotExist: Symbol not found.", e.message, t+"C2");
        }
    }

    public: static void generateIdValue(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, &comp.program.globalScope);

        //1. Set an entry point
        llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
        llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
        ctx.builder.SetInsertPoint(block);

        //2. Declare a couple of symbols
        auto symbol = std::make_shared<EulSymbol>(
            yy::EulParser::token::VAR,
            comp.program.nativeTypes.stringType,
            std::make_shared<EulIntToken>(123, 32, false)
        );
        symbol->llvmValue = ctx.builder.CreateAlloca(llvm::IntegerType::get(ctx.context, 32), nullptr, "someIntVar");
        auto store = ctx.builder.CreateStore(
            llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 123, true),
            symbol->llvmValue
        );
        comp.program.globalScope.declare("someIntVar", symbol);

        symbol = std::make_shared<EulSymbol>(
            yy::EulParser::token::VAR,
            comp.program.nativeTypes.float32Type,
            std::make_shared<EulFloatToken>(7.5, 32)
        );
        symbol->llvmValue = llvm::ConstantFP::get(comp.program.nativeTypes.float32Type->getLlvmType(&ctx), 7.5);
        comp.program.globalScope.declare("someFloatLiteral", symbol);

        //3. Get the type of the symbols
        EulIdToken tok("someFloatLiteral", &comp.program.globalScope);
        auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::llvmFloatConstant(llvmValue, 32, 7.5, 0.001, t+"A1");
        Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"A2"); //we start with 2 commands in the block: the alloca and the store.

        tok.name.assign("Int32");
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
        Assert::null(llvmValue, t+"B1");
        Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"B2");


        //4. Try accessing a non existing symbol
        try {
            tok.name.assign("iDoNotExist");
            llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
            Assert::fail(t+" Expected exception due to non existing symbol, but none was thrown.");
        }
        catch(EulError e) {
            Assert::equals(SEMANTIC, e.type, t+"D1");
            Assert::equals("iDoNotExist: Symbol not found.", e.message, t+"D2");
            Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"D3");
        }

        //5. Try again with EulCodeGenFlags_LOAD_VAR flags this should generate a load instruction
        tok.name.assign("someIntVar");
        llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_LOAD_VAR);
        Assert::that(llvm::LoadInst::classof(llvmValue), t+"E1");

        auto asLoadInstr = static_cast<llvm::LoadInst*>(llvmValue);
        Assert::equals(3, ctx.builder.GetInsertBlock()->size(), t+"E3");
    }
    //endregion



    public: static void runAll() {
        generateCharValue("EulTokenCodeGenTest.generateCharValue ");
        generateCharEulType("EulTokenCodeGenTest.generateCharEulType ");

        generateFloatValue("EulTokenCodeGenTest.generateFloatValue ");
        generateFloatEulType("EulTokenCodeGenTest.generateFloatEulType ");

        generateIntValue("EulTokenCodeGenTest.generateIntValue ");
        generateIntEulType("EulTokenCodeGenTest.generateIntEulType ");

        generateStringValue("EulTokenCodeGenTest.generateStringValue ");
        generateStringEulType("EulTokenCodeGenTest.generateStringEulType ");

        generateIdValue("EulTokenCodeGenTest.generateIdValue ");
        generateIdEulType("EulTokenCodeGenTest.generateIdEulType ");
    }
};