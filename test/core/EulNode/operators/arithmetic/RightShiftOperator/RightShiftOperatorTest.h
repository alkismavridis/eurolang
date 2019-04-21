#pragma once





class RightShiftOperatorTest {
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


  public: static void runAll() {
    rightShiftOperatorInfixTest("RightShiftOperatorTest.rightShiftOperatorInfixTest ");
  }
};
