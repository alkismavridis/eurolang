#pragma once





class EulStringNodeTest {
  public: static void constructorTest(const std::string& t) {
      std::string str = "someName";
      EulStringNode tok = EulStringNode(str);
      Assert::equals("someName", tok.value, t+"A1");

      str = "someOtherName";
      EulStringNode tok2 = EulStringNode(str);
      Assert::equals("someOtherName", tok2.value, t+"A2");

      //check that first token did not change
      Assert::equals("someName", tok.value, t+"A3");


      //check type getter
      Assert::enumEquals(EulNodeType::STRING, tok.getNodeType(), t+"A4");
  }


  public: static void generateValue(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a string and get its value
      EulStringNode tok("hello\n");
      auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmStringConstant(llvmValue, "hello\n", &ctx, t+"A1");

      //2. Create a string and get its value
      EulStringNode tok2("one_two\n");
      llvmValue = tok2.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmStringConstant(llvmValue, "one_two\n", &ctx, t+"A2");

  }

  public: static void getEulType(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a string token and check its type
      EulStringNode tok("hello\n");
      auto eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.stringType.get(), t+"A1");
  }


  public: static void runAll() {
    constructorTest("EulStringNodeTest.constructorTest ");
    generateValue("EulStringNodeTest.generateValue ");
    getEulType("EulStringNodeTest.getEulType ");
  }
};
