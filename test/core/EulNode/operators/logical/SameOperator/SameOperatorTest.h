#pragma once





class SameOperatorTest {
  public: static void sameOperatorTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test integer equality
      std::shared_ptr<EulType> resultType;
      auto result = EUL_OPERATORS.sameOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 30, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"A1 positive int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"A2 positive int result type");

      resultType = nullptr;
      result = EUL_OPERATORS.sameOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 16), 30, true),
          comp.program.nativeTypes.int16Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 35, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"B1 negative int result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"B2 negative int result type");


      //3. Test float addition
      resultType = nullptr;
      result = EUL_OPERATORS.sameOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 1, t+"C1 positive float result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"C2 positive float result type");

      resultType = nullptr;
      result = EUL_OPERATORS.sameOperator.performInfix(
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float32Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.5),
          comp.program.nativeTypes.float32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 1, 0, t+"D1 negative float result");
      Assert::equals(comp.program.nativeTypes.booleanType.get(), resultType.get(), t+"D2 negative float result type");
  }


  public: static void runAll() {
    sameOperatorTest("SameOperatorTest.sameOperatorTest ");
  }
};
