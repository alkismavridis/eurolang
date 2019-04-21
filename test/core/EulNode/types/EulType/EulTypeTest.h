#pragma once





class EulTypeTest {


  public: static void isEulTypeTest(const std::string& t) {
      //1. Test a couple of positive cases
      EulType type = EulIntegerType(64, true);
      Assert::that(EulType::isEulType(&type), t+"A1");

      EulNamedType type2 = EulNamedType("SomeCoolType");
      Assert::that(EulType::isEulType(&type2), t+"A2");

      EulPointerType type3 = EulPointerType(&type, 1);
      Assert::that(EulType::isEulType(&type3), t+"A3");

      //2. Test a negative case: not a AST
      EulStringNode notAType1 = EulStringNode("123");
      Assert::thatNot(EulType::isEulType(&notAType1), t+"A4");

      //3. Test a negative case: AST, but not a EulType
      ReturnStatement notAType2 = ReturnStatement(std::make_shared<EulStringNode>("456"));
      Assert::thatNot(EulType::isEulType(&notAType2), t+"A5");
  }





  //region SPLIT THIS TO MULTIPLE FILES
  public: static void getLlvmTypeForPrimitivesTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Test a couple of ints
      Assert::equals(llvm::IntegerType::get(ctx.context, 8), comp.program.nativeTypes.int8Type->getLlvmType(&ctx), t+"A1");
      Assert::equals(llvm::IntegerType::get(ctx.context, 32), comp.program.nativeTypes.uint32Type->getLlvmType(&ctx), t+"A2");

      //2. Test a couple of chars
      Assert::equals(llvm::IntegerType::get(ctx.context, 8), comp.program.nativeTypes.char8Type->getLlvmType(&ctx), t+"B1");
      Assert::equals(llvm::IntegerType::get(ctx.context, 32), comp.program.nativeTypes.char32Type->getLlvmType(&ctx), t+"B2");

      //3. Test a couple of floats
      Assert::equals(llvm::Type::getFloatTy(ctx.context), comp.program.nativeTypes.float32Type->getLlvmType(&ctx), t+"C1");
      Assert::equals(llvm::Type::getDoubleTy(ctx.context), comp.program.nativeTypes.float64Type->getLlvmType(&ctx), t+"C2");
      try {
          EulFloatType wrongType(35);
          wrongType.getLlvmType(&ctx);
          Assert::fail(t+" Exception expected due to wrong float type size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C3");
          Assert::equals("Invalid floating point size: 35. Please use one of 32, 64.", e.message, t+"C4");
      }

      //4. String type
      Assert::equals(llvm::IntegerType::get(ctx.context, 8)->getPointerTo(), comp.program.nativeTypes.stringType->getLlvmType(&ctx), t+"D1");
  }
  //endregion




  //region CODE GENERATION UTIL TESTS
  public: static void doCommonIntMergingTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      auto& nativeTypes = comp.program.nativeTypes;

      //1. Check size behaviour (bigger one is returned, unsigned wins)
      auto result = EulType::doCommonIntMerging(nativeTypes.int32Type, nativeTypes.int32Type, &ctx);
      Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A1 same types return itself.");

      result = EulType::doCommonIntMerging(nativeTypes.int16Type, nativeTypes.int32Type, &ctx);
      Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A2 bigger type is returned");

      result = EulType::doCommonIntMerging(nativeTypes.uint32Type, nativeTypes.int32Type, &ctx);
      Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A3 unsigned wins");

      result = EulType::doCommonIntMerging(nativeTypes.uint16Type, nativeTypes.int32Type, &ctx);
      Assert::equals(nativeTypes.uint32Type.get(), result.get(), t+"A4 unsigned and bigger wins");

      result = EulType::doCommonIntMerging(nativeTypes.int8Type, nativeTypes.int16Type, &ctx);
      Assert::equals(nativeTypes.int16Type.get(), result.get(), t+"A5 bigger type is returned.");


      //2. Fail case: test invalid int sizes
      try {
          EulType::doCommonIntMerging(std::make_shared<EulIntegerType>(67, false), nativeTypes.int32Type, &ctx);
          Assert::fail(t+" Expected exception due to invalid int size, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Wrong int size: 67", e.message, t+"B2");
      }


      //3. Fail case: test non integer types
      try {
          EulType::doCommonIntMerging(nativeTypes.stringType, nativeTypes.int32Type, &ctx);
          Assert::fail(t+" Expected exception due to invalid casting to int, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C1");
          Assert::equals("Invalid conversion to int.", e.message, t+"C2");
      }
  }

  public: static void doCommonFloatMergingTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      auto& nativeTypes = comp.program.nativeTypes;

      //1. Check size behaviour (bigger one is returned)
      auto result = EulType::doCommonFloatMerging(nativeTypes.float32Type, nativeTypes.float32Type, &ctx);
      Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"A1 same types return itself.");

      result = EulType::doCommonFloatMerging(nativeTypes.float64Type, nativeTypes.float64Type, &ctx);
      Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A2 same types return itself.");

      result = EulType::doCommonFloatMerging(nativeTypes.float64Type, nativeTypes.float32Type, &ctx);
      Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A3 same types return itself.");

      result = EulType::doCommonFloatMerging(nativeTypes.float32Type, nativeTypes.float64Type, &ctx);
      Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"A4 same types return itself.");


      //2. Fail case: test invalid int sizes
      try {
          EulType::doCommonFloatMerging(std::make_shared<EulFloatType>(67), nativeTypes.float64Type, &ctx);
          Assert::fail(t+" Expected exception due to invalid float size, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Wrong float size: 67", e.message, t+"B2");
      }

      //3. Test non float input parameter
      try {
          EulType::doCommonFloatMerging(nativeTypes.stringType, nativeTypes.float32Type, &ctx);
          Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C1");
          Assert::equals("Invalid conversion to float.", e.message, t+"C2");
      }
  }

  public: static void doCommonNumberMergingTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      auto& nativeTypes = comp.program.nativeTypes;


      //1.test both int
      auto result = EulType::doCommonNumberMerging(nativeTypes.int32Type, nativeTypes.int8Type, &ctx);
      Assert::equals(nativeTypes.int32Type.get(), result.get(), t+"A1 both integers");

      //2.test left float and right int right
      result = EulType::doCommonNumberMerging(nativeTypes.float32Type, nativeTypes.int8Type, &ctx);
      Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"B1 left float, right integer");

      //3.test right float and left int
      result = EulType::doCommonNumberMerging(nativeTypes.int8Type, nativeTypes.float32Type, &ctx);
      Assert::equals(nativeTypes.float32Type.get(), result.get(), t+"B2 right float, left integer");

      //4. test both floats
      result = EulType::doCommonNumberMerging(nativeTypes.float64Type, nativeTypes.float32Type, &ctx);
      Assert::equals(nativeTypes.float64Type.get(), result.get(), t+"C1 right float, left integer");

      //5. test other type
      try {
          EulType::doCommonNumberMerging(nativeTypes.stringType, nativeTypes.float32Type, &ctx);
          Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"D1");
          Assert::equals("Invalid conversion to number.", e.message, t+"D2");
      }

      try {
          EulType::doCommonNumberMerging(nativeTypes.float32Type, nativeTypes.stringType, &ctx);
          Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"E1");
          Assert::equals("Invalid conversion to number.", e.message, t+"E2");
      }

      try {
          EulType::doCommonNumberMerging(nativeTypes.int32Type, nativeTypes.stringType, &ctx);
          Assert::fail(t+" Expected exception due to invalid casting to float, but none was thrown.");
      }
      catch (EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"F1");
          Assert::equals("Invalid conversion to number.", e.message, t+"F2");
      }
  }
  //endregion


  public: static void runAll() {
    Assert::warnNotTested("EulTypeTest::getPointerTo");

    getLlvmTypeForPrimitivesTest("EulTypeTest.getLlvmTypeForPrimitivesTest ");


    //Code Gen utils Tests
    Assert::warnNotTested("EulPointerTypeTest");
    isEulTypeTest("EulAstTest.isEulTypeTest ");

    doCommonIntMergingTest("EulTypeCodeGenTest.doCommonIntMergingTest ");
    doCommonFloatMergingTest("EulTypeCodeGenTest.doCommonFloatMergingTest ");
    doCommonNumberMergingTest("EulTypeCodeGenTest.doCommonNumberMerging ");
  }
};
