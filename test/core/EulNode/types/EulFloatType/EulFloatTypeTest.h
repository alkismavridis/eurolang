#pragma once





class EulFloatTypeTest {
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


  public: static void runAll() {
    Assert::warnNotTested("EulFloatTypeTest::getLlvmType");
    castIntToFloatValueTest("EulFloatTypeTest.castIntToFloatValueTest ");
    castFloatToFloatValueTest("EulFloatTypeTest.castFloatToFloatValueTest ");
  }
};
