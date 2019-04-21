#pragma once



class EulIntNodeTest {
  public: static void constructorTest(const std::string& t) {
      //1. test int literals without qualifiers
      char str[] = "123";
      EulIntNode tok = EulIntNode(str);
      Assert::equals(123, tok.value, t + "A1");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "A2");
      Assert::thatNot(tok.isUnsigned, t + "A3");

      char str2[] = "0";
      tok = EulIntNode(str2);
      Assert::equals(0, tok.value, t + "A4");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "A5");
      Assert::thatNot(tok.isUnsigned, t + "A6");


      //2. test int literals with signed/unsigned qualifiers
      char str3[] = "55u";
      tok = EulIntNode(str3);
      Assert::equals(55, tok.value, t + "B1");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B2");
      Assert::that(tok.isUnsigned, t + "B3");

      char str4[] = "0u";
      tok = EulIntNode(str4);
      Assert::equals(0, tok.value, t + "B4");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B5");
      Assert::that(tok.isUnsigned, t + "B6");

      char str5[] = "55s";
      tok = EulIntNode(str5);
      Assert::equals(55, tok.value, t + "B7");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B8");
      Assert::thatNot(tok.isUnsigned, t + "B9");

      char str6[] = "0s";
      tok = EulIntNode(str6);
      Assert::equals(0, tok.value, t + "B10");
      Assert::equals(EUL_LANG_DEFAULT_INT_SIZE, tok.size, t + "B11");
      Assert::thatNot(tok.isUnsigned, t + "B12");

      //3. test int literals with signed/unsigned qualifiers and sizes
      char str7[] = "55u12";
      tok = EulIntNode(str7);
      Assert::equals(55, tok.value, t + "C1");
      Assert::equals(12, tok.size, t + "C2");
      Assert::that(tok.isUnsigned, t + "C3");

      char str8[] = "0u6";
      tok = EulIntNode(str8);
      Assert::equals(0, tok.value, t + "C4");
      Assert::equals(6, tok.size, t + "C5");
      Assert::that(tok.isUnsigned, t + "C6");

      char str9[] = "55s123";
      tok = EulIntNode(str9);
      Assert::equals(55, tok.value, t + "C7");
      Assert::equals(123, tok.size, t + "C8");
      Assert::thatNot(tok.isUnsigned, t + "C9");

      char str10[] = "0s55";
      tok = EulIntNode(str10);
      Assert::equals(0, tok.value, t + "C10");
      Assert::equals(55, tok.size, t + "C11");
      Assert::thatNot(tok.isUnsigned, t + "C12");


      //check type getter
      Assert::enumEquals(EulNodeType::INT, tok.getNodeType(), t+"D1");
  }


  public: static void generateValue(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulIntNode tok(123, 8, false);
      auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 8, 123, t+"A1");

      //2. Test various sizes and values (signed)
      tok.size = 16;
      tok.value = 456;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 16, 456, t+"A2");

      tok.size = 32;
      tok.value = 52767;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 32, 52767, t+"A3");

      tok.size = 64;
      tok.value = 3147483647;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 64, 3147483647, t+"A4");


      //3. Test various sizes and values (unsigned)
      tok.isUnsigned = true;
      tok.size = 8;
      tok.value = 200;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 8, 200, t+"B1");

      tok.size = 16;
      tok.value = 456;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 16, 456, t+"B2");

      tok.size = 32;
      tok.value = 69535;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 32, 69535, t+"B3");

      tok.size = 64;
      tok.value = 7294967295;
      llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(llvmValue, 64, 7294967295, t+"B4");

      //4. Test an invalid size (both signed and unsigned)
      tok.size = 33;
      tok.isUnsigned = false;
      try {
          llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C1");
          Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"C2");
      }

      tok.size = 33;
      tok.isUnsigned = true;
      try {
          llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"D1");
          Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"D2");
      }
  }


  public: static void getEulType(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a char token and get its llvm value
      EulIntNode tok(123, 8, false);
      auto eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.int8Type.get(), t+"A1");

      //2. Test various sizes and values (signed)
      tok.size = 16;
      tok.value = 456;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.int16Type.get(), t+"A2");

      tok.size = 32;
      tok.value = 52767;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.int32Type.get(), t+"A3");

      tok.size = 64;
      tok.value = 3147483647;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.int64Type.get(), t+"A4");


      //3. Test various sizes and values (unsigned)
      tok.isUnsigned = true;
      tok.size = 8;
      tok.value = 200;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.uint8Type.get(), t+"B1");

      tok.size = 16;
      tok.value = 456;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.uint16Type.get(), t+"B2");

      tok.size = 32;
      tok.value = 69535;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.uint32Type.get(), t+"B3");

      tok.size = 64;
      tok.value = 7294967295;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.uint64Type.get(), t+"B4");

      //4. Test an invalid size (both signed and unsigned)
      tok.size = 33;
      tok.isUnsigned = false;
      try {
          eulType = tok.getEulType(&ctx, 0);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C1");
          Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"C2");
      }

      tok.size = 33;
      tok.isUnsigned = true;
      try {
          eulType = tok.getEulType(&ctx, 0);
          Assert::fail(t+" Expected exception due to invalid size, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"D1");
          Assert::equals("Invalid integer size: 33. Please use one of 8, 16, 32, 64.", e.message, t+"D2");
      }
  }


  public: static void runAll() {
    constructorTest("EulIntNodeTest.constructorTest ");
    generateValue("EulIntNodeTest.generateValue ");
    getEulType("EulIntNodeTest.getEulType ");
  }
};
