#pragma once





class EulCharNodeTest {

  public: static void constructorTest(const std::string& t) {
      Compiler comp(0);

      //1. check one char long
      std::string str = "'a'";
      EulCharNode tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "A1");
      Assert::equals('a', tok.value, t + "A2");
      Assert::equals(8, tok.size, t + "A3");

      str = "'~'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "A4");
      Assert::equals('~', tok.value, t + "A5");
      Assert::equals(8, tok.size, t + "A6");


      //2. check two chars long
      str = "'ϋ'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "B1");
      Assert::equals(0xcf8b, tok.value, t + "B2");
      Assert::equals(16, tok.size, t + "B3");

      str = "'ώ'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "C1");
      Assert::equals(0xcf8e, tok.value, t + "C2");
      Assert::equals(16, tok.size, t + "C3");

      str = "'π'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "D1");
      Assert::equals(0xcf80, tok.value, t + "D2");
      Assert::equals(16, tok.size, t + "D3");

      str = "'ü'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "F1");
      Assert::equals(0xc3bc, tok.value, t + "F2");
      Assert::equals(16, tok.size, t + "F3");

      //3. check 4 bytes long unicodes
      str = "'𠜎'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "G1");
      Assert::equalsUnsigned(0xf0a09c8e, tok.value, t + "G2");
      Assert::equals(32, tok.size, t + "G3");

      str = "'𡇙'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "H1");
      Assert::equalsUnsigned(0xf0a18799, tok.value, t + "H2");
      Assert::equals(32, tok.size, t + "H3");

      str = "'😌'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "I1");
      Assert::equalsUnsigned(0xf09f988c, tok.value, t + "I2");
      Assert::equals(32, tok.size, t + "I3");

      str = "'🙋'";
      tok = EulCharNode(str.c_str(), str.length(), &comp);
      Assert::equals(0, comp.errors.size(), t + "J1");
      Assert::equalsUnsigned(0xf09f998b, tok.value, t + "J2");
      Assert::equals(32, tok.size, t + "J3");


      //check type getter
      Assert::enumEquals(EulNodeType::CHAR, tok.getNodeType(), t+"K1");
  }

  public: static void generateValue(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulCharNode tok('b', 8);
      auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 8, (int)'b', t+"A1");

      //2. Test various sizes and values
      tok.size = 16;
      tok.value = 0xcf8e; //greek ώ
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 16, 0xcf8e, t+"A2");

      tok.size = 32;
      tok.value = 0xf0a09c8e; //chinese 𠜎
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 32, 0xf0a09c8e, t+"A3");

      //3. Test an invalid size
      tok.size = 64;
      try {
          llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Invalid character size: 64. Please use one of 8, 16, 32.", e.message, t+"B2");
      }
  }


  public: static void getEulType(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulCharNode tok('b', 8);
      auto eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.char8Type.get(), t+"A1");

      //2. Test various sizes and values
      tok.size = 16;
      tok.value = 0xcf8e; //greek ώ
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.char16Type.get(), t+"A2");

      tok.size = 32;
      tok.value = 0xf0a09c8e; //chinese 𠜎
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.char32Type.get(), t+"A3");

      //3. Test an invalid size
      tok.size = 64;
      try {
          eulType = tok.getEulType(&ctx, 0);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Invalid character size: 64. Please use one of 8, 16, 32.", e.message, t+"B2");
      }
  }


  public: static void runAll() {
    constructorTest("EulCharNodeTest.constructorTest ");
    generateValue("EulCharNodeTest.generateValue ");
    getEulType("EulCharNodeTest.getEulType ");
  }
};
