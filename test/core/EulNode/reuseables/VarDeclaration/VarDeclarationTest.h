#pragma once





class VarDeclarationTest {


  public: static void getEulType(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Create a var declaration
      VarDeclaration tok(
          std::make_shared<EulSymbolNameNode>("hello", ctx.currentScope),
          comp.program.nativeTypes.float32Type,           //the symbol has type Float32, but its value is a Float64 literal
          std::make_shared<EulFloatNode>(7.5, 64)
      );

      //2. Get its eul type when both declared type and value are present. The declared type must be returned
      auto eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A1");

      //3. Try a declaration without a defined type. The values type should be returned
      tok.varType = nullptr;
      eulType = tok.getEulType(&ctx, 0);
      Assert::equals(eulType.get(), comp.program.nativeTypes.float64Type.get(), t+"A2");


      //3. Try a declaration without any of the two. An exception should be thrown.
      try {
          tok.value = nullptr;
          eulType = tok.getEulType(&ctx, 0);
          Assert::fail(t+"Exception expected due to var declaration with that lacks both type and value. But none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::NOT_IMPLEMENTED, e.type, t+"A3");
          Assert::equals("NOT IMPLEMENTED: variable without initial value.", e.message, t+"A4");
      }
  }


  public: static void runAll() {
    getEulType("VarDeclarationTest.getEulType ");
  }
};
