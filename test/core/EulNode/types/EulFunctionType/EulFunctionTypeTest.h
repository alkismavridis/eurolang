#pragma once





class EulFunctionTypeTest {
  public: static void functionTypeTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);


      //1. Create an eul function type with return type and parameters
      auto eulType = EulFunctionType(comp.program.nativeTypes.stringType);
      eulType.argTypes.push_back(comp.program.nativeTypes.int32Type);
      eulType.argTypes.push_back(comp.program.nativeTypes.int64Type);
      auto llvmType = eulType.getLlvmType(&ctx);

      //2. Assert result.
      Assert::that(llvm::FunctionType::classof(llvmType), t+"A1");
      auto asFunc = static_cast<llvm::FunctionType*>(llvmType);

      Assert::equals(comp.program.nativeTypes.stringType->getLlvmType(&ctx), asFunc->getReturnType(), t+"A2");
      Assert::equals(2, asFunc->getNumParams(), t+"A3");
      Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asFunc->getParamType(0), t+"A4");
      Assert::equals(comp.program.nativeTypes.int64Type->getLlvmType(&ctx), asFunc->getParamType(1), t+"A5");

      //3. Build a function without parameters and no return type
      auto eulType2 = EulFunctionType(comp.program.nativeTypes.voidType);
      llvmType = eulType2.getLlvmType(&ctx);

      //4. Check result
      Assert::that(llvm::FunctionType::classof(llvmType), t+"B1");
      asFunc = static_cast<llvm::FunctionType*>(llvmType);
      Assert::that(asFunc->getReturnType()->isVoidTy(), t+"B2");
      Assert::equals(0, asFunc->getNumParams(), t+"B3");

      Assert::warnNotTested("EulFunctionTypeTest.functionTypeTest -- all constructors");
  }


  public: static void runAll() {
    Assert::warnNotTested("EulFunctionTypeTest.castValue");
    Assert::warnNotTested("EulFunctionTypeTest.isParameterCountValid");
    functionTypeTest("EulFunctionTypeTest.functionTypeTest ");
  }
};
