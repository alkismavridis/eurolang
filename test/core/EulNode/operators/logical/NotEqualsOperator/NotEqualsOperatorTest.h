#pragma once





class NotEqualsOperatorTest {
  public: static void notEqualsOperatorTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test integer equality
      std::shared_ptr<EulType> resultType;
      auto result = EUL_OPERATORS.notEqualsOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"A1 negative int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 negative int result type");

      resultType = nullptr;
      result = EUL_OPERATORS.notEqualsOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"B1 positive int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 positive int result type");


      //3. Test float addition
      resultType = nullptr;
      result = EUL_OPERATORS.notEqualsOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"C1 negative float result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 negative float result type");

      resultType = nullptr;
      result = EUL_OPERATORS.notEqualsOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
          comp.program.nativeTypes.float32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"D1 positive float result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 positive float result type");
  }


  public: static void runAll() {
    notEqualsOperatorTest("NotEqualsOperatorTest.notEqualsOperatorTest ");
  }
};
