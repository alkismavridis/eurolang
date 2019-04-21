#pragma once

class EulPointerTypeTest {



    //region TYPE TESTS
    public: static void getPointerTo(const std::string& t) {
        //1. Create a type to point to.
        auto type = std::make_shared<EulIntegerType>(64, true);

        //2. Mate the pointer
        EulPointerType ptrType = EulPointerType(type.get(), 4);

        //3. Make assertions
        Assert::equals(type.get(), ptrType.contentType, t+"A1");
        Assert::equals(4, ptrType.depth, t+"A2");
        Assert::enumEquals(EulTypeEnum::POINTER_TYPE, ptrType.getTypeEnum(), t+"A3");
    }

    public: static void pointerTypeTest(const std::string& t) {
        Compiler comp(0);
        llvm::LLVMContext llvmCtx;
        llvm::Module module("dummyName", llvmCtx);
        EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);


        //1. Create a pointer
        EulPointerType ptrType(comp.program.nativeTypes.float32Type.get(), 3);
        auto expected = llvm::Type::getFloatTy(ctx.context)
            ->getPointerTo()
            ->getPointerTo()
            ->getPointerTo();

        Assert::equals(expected, ptrType.getLlvmType(&ctx), t+"A1");
    }
    //endregion



    public: static void runAll() {
      Assert::warnNotTested("EulPointerTypeTest::castValue");
      getPointerTo("EulPointerTypeTest.getPointerTo ");
      pointerTypeTest("EulPointerTypeTest.pointerTypeTest ");
    }
};
