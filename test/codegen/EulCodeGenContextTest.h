#pragma once



class EulCodeGenContextTest {
    //region GLOBAL VARIABLE GENERATION
    public: static void makeGlobalLiteralTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

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


    public: static void runAll() {
        makeGlobalLiteralTest("EulCodeGenContextTest.makeGlobalLiteralTest ");
    }
};