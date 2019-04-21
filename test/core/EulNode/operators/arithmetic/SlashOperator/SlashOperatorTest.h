#pragma once





class SlashOperatorTest {

  public: static void slashOperatorTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test same sized operations
      std::shared_ptr<EulType> resultType;
      auto result = EUL_OPERATORS.slashOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 44, true),
          comp.program.nativeTypes.int32Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 11, true),
          comp.program.nativeTypes.int32Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 32, 4, t+"A1");
      Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A1 result type");

      //2. Test different sizes
      result = EUL_OPERATORS.slashOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, true),
          comp.program.nativeTypes.int8Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 64), 3, true),
          comp.program.nativeTypes.int64Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 64, 3, t+"A2");
      Assert::equals(comp.program.nativeTypes.int64Type.get(), resultType.get(), t+"A2 result type");

      //3. Test a case where sign matters (signed)
      result = EUL_OPERATORS.slashOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100 (156)
          comp.program.nativeTypes.int8Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
          comp.program.nativeTypes.int8Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 8, 206, t+"B1 signed integer division"); //signed version of -100/2 gives -50, which is 11001110 (206)
      Assert::equals(comp.program.nativeTypes.int8Type.get(), resultType.get(), t+"B1 result type");

      //4. Test a case where sign matters (unsigned)
      result = EUL_OPERATORS.slashOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), -100, true), //-100 is 10011100 (156)
          comp.program.nativeTypes.int8Type,
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 2, true),
          comp.program.nativeTypes.uint8Type,
          &resultType,
          &ctx
      );
      Assert::llvmIntConstant(result, 8, 78, t+"B2 unsigned integer division"); //unsigned version of -100/2 this should become 10011100b / 2, which is 01001110 (78)
      Assert::equals(comp.program.nativeTypes.uint8Type.get(), resultType.get(), t+"B2 result type");


      //5. Test float addition
      result = EUL_OPERATORS.slashOperator.performInfix(
          llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 8), 10, false),
          comp.program.nativeTypes.uint8Type,
          llvm::ConstantFP::get(llvm::Type::getDoubleTy(ctx.context), 3.2),
          comp.program.nativeTypes.float64Type,
          &resultType,
          &ctx
      );
      Assert::llvmFloatConstant(result, 64, 3.125, 0.001, t+"C1");
      Assert::equals(comp.program.nativeTypes.float64Type.get(), resultType.get(), t+"C2 result type");
  }

  public: static void runAll() {
    slashOperatorTest("SlashOperatorTest.slashOperatorTest ");
  }
};
