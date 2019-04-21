#pragma once





class MinusOperatorTest {
  public: static void minusOperatorTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test same sized operations
      std::shared_ptr<EulType> resultType;
      auto result = EUL_OPERATORS.minusOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 234, true),
          comp.program.nativeTypes.int32Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 34, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 32, 200, t+"A1");
      Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

      //2. Test different sizes.
      result = EUL_OPERATORS.minusOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 50, true),
          comp.program.nativeTypes.int8Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 10, true),
          comp.program.nativeTypes.int16Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 16, 40, t+"A2");
      Assert::equals(comp.program.nativeTypes.int16Type.get(), resultType.get(), t+"A2 result type");


      //3. Test float addition
      result = EUL_OPERATORS.minusOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -1, false),
          comp.program.nativeTypes.uint8Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 4.23),
          comp.program.nativeTypes.float64Type,
          &resultType,
          &ctx
      );
      Assert::llvmFloatConstant(result, 64, 250.77, 0.0001, t+"A3"); //-1 will result to 255, because we treated it as UInt8
      Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"A3 result type");
  }


  public: static void runAll() {
    minusOperatorTest("MinusOperatorTest.minusOperatorTest ");
  }
};
