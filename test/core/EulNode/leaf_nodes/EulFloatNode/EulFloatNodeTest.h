#pragma once





class EulFloatNodeTest {

  public: static void constructorTest(const std::string& t) {

      //1. test case where int and decimal parst are present
      char str[] = "1.2";
      EulFloatNode tok = EulFloatNode(str);
      Assert::equals(1.2, tok.value, 0.0001, t + "A1");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A2");

      char str2[] = "0.0";
      tok = EulFloatNode(str2);
      Assert::equals(0.0, tok.value, 0.0001, t + "A3");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A4");

      char str3[] = "5.0";
      tok = EulFloatNode(str3);
      Assert::equals(5.0, tok.value, 0.0001, t + "A5");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A6");

      char str4[] = "0.7";
      tok = EulFloatNode(str4);
      Assert::equals(0.7, tok.value, 0.0001, t + "A7");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "A8");


      //2. int part missing, or float part missing
      char str5[] = "0.";
      tok = EulFloatNode(str5);
      Assert::equals(0.0, tok.value, 0.0001, t + "B1");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B2");

      char str6[] = "234.0";
      tok = EulFloatNode(str6);
      Assert::equals(234.0, tok.value, 0.0001, t + "B3");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B4");

      char str7[] = ".0";
      tok = EulFloatNode(str7);
      Assert::equals(0.0, tok.value, 0.0001, t + "B5");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B6");

      char str8[] = ".536";
      tok = EulFloatNode(str8);
      Assert::equals(0.536, tok.value, 0.0001, t + "B7");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "B8");


      //3. casting with size
      char str9[] = "0f4";
      tok = EulFloatNode(str9);
      Assert::equals(0, tok.value, 0.0001, t + "C1");
      Assert::equals(4, tok.size, t + "C2");

      char str10[] = "1f32";
      tok = EulFloatNode(str10);
      Assert::equals(1, tok.value, 0.0001, t + "C3");
      Assert::equals(32, tok.size, t + "C4");

      char str11[] = "1.4f32";
      tok = EulFloatNode(str11);
      Assert::equals(1.4, tok.value, 0.0001, t + "C5");
      Assert::equals(32, tok.size, t + "C6");

      char str12[] = ".4f12";
      tok = EulFloatNode(str12);
      Assert::equals(0.4, tok.value, 0.0001, t + "C7");
      Assert::equals(12, tok.size, t + "C8");

      char str13[] = "3.3f15";
      tok = EulFloatNode(str13);
      Assert::equals(3.3, tok.value, 0.0001, t + "C9");
      Assert::equals(15, tok.size, t + "C10");


      //4. casting default size      0f 1f+1.f .4f = 3.3f"
      char str14[] = "0f";
      tok = EulFloatNode(str14);
      Assert::equals(0, tok.value, 0.0001, t + "D1");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D2");

      char str15[] = "1f";
      tok = EulFloatNode(str15);
      Assert::equals(1, tok.value, 0.0001, t + "D3");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D4");

      char str16[] = "2.f";
      tok = EulFloatNode(str16);
      Assert::equals(2.0, tok.value, 0.0001, t + "D5");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D6");

      char str17[] = ".4f";
      tok = EulFloatNode(str17);
      Assert::equals(0.4, tok.value, 0.0001, t + "D7");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D8");

      char str18[] = "3.3f";
      tok = EulFloatNode(str18);
      Assert::equals(3.3, tok.value, 0.0001, t + "D7");
      Assert::equals(EUL_LANG_DEFAULT_FLOAT_SIZE, tok.size, t + "D8");


      //check type getter
      Assert::enumEquals(EulNodeType::FLOAT, tok.getNodeType(), t+"E1");

  }

  public: static void generateValue(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulFloatNode tok(12.5, 32);
      auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmFloatConstant(llvmValue, 32, 12.5, 0.001, t+"A1");

      //2. Test various sizes and values
      tok.size = 64;
      tok.value = 123.7;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmFloatConstant(llvmValue, 64, 123.7, 0.001, t+"A2");

      //3. Test an invalid size
      tok.size = 14;
      try {
          llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Invalid floating point size: 14. Please use one of 32, 64.", e.message, t+"B2");
      }
  }


  public: static void getEulType(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulFloatNode tok(12.5, 32);
      auto eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A1");

      //2. Test various sizes and values
      tok.size = 64;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.float64Type.get(), t+"A2");

      //3. Test an invalid size
      tok.size = 14;
      try {
          eulType = tok.getEulType(&ctx, 0);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Invalid floating point size: 14. Please use one of 32, 64.", e.message, t+"B2");
      }
  }


  public: static void runAll() {
    constructorTest("EulFloatNodeTest.constructorTest ");
    generateValue("EulFloatNodeTest.generateValue ");
    getEulType("EulFloatNodeTest.getEulType ");
  }
};
