#pragma once





class LeftShiftOperatorTest {
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


  public: static void runAll() {
    leftShiftOperatorInfixTest("LeftShiftOperatorTest.leftShiftOperatorInfixTest ");
  }
};
