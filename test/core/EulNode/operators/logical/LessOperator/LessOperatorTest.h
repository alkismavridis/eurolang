#pragma once





class LessOperatorTest {
  public: static void lessOperatorTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test signed integers
      std::shared_ptr<EulType> resultType;
      auto result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"A1 positive signed int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive signed int result type");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"B1 negative signed int result (equals)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive signed int result type (equals)");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 55, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"C1 negative signed int result (greater)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive signed int result type (greater)");

      //2. Test unsigned integers
      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 1, true),
          comp.program.nativeTypes.uint16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.uint32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"D1 positive unsigned int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive unsigned int result type");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 35, true),
          comp.program.nativeTypes.uint16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.uint32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"E1 negative unsigned int result (equals)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"E2 negative unsigned int result type (equals)");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), -1, true), //-1 should be interpreted as unsigned int16, which is a large number.
          comp.program.nativeTypes.uint16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.uint32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"F1 negative unsigned int result (greater)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"F2 negative unsigned int result type (greater)");



      //3. Test floats
      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), -6.7),
          comp.program.nativeTypes.float64Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float64Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"G1 positive float result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"G2 positive float result type");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float64Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float64Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"H1 negative float result (equals)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"H2 negative float result type (equals)");

      resultType = nullptr;
      result = EUL_OPERATORS.lessOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 10.0),
          comp.program.nativeTypes.float64Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float64Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"I1 negative float result (greater)");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"I2 negative float result type (greater)");
  }


  public: static void runAll() {
    lessOperatorTest("LessOperatorTest.lessOperatorTest ");
  }
};
