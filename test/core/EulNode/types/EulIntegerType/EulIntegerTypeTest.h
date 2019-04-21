#pragma once





class EulIntegerTypeTest {
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
          Assert::enumEquals(EulErrorType::NOT_IMPLEMENTED, e.type, t+"C1");
          Assert::equals("NOT_IMPLEMENTED only ints can be casted to ints.", e.message, t+"C2");
      }
  }


  public: static void runAll() {
    Assert::warnNotTested("EulIntegerTypeTest::getLlvmType");
    castToIntegerTest("EulIntegerTypeTest.castToIntegerTest ");
  }
};
