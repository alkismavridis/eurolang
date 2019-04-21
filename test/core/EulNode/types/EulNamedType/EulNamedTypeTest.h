#pragma once





class EulNamedTypeTest {
  public: static void namedTypeTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);


      //1. Define a named type
      auto namedLlvmType = llvm::StructType::create(ctx.context, "MyCoolType");
      namedLlvmType->setBody(llvm::ArrayRef<llvm::Type*>(
          llvm::IntegerType::get(ctx.context, 8)->getPointerTo()
      ));


      //2. Create a Named type and try accessing llvm type. It should fetched exactly namedLlvmType
      EulNamedType namedEulType("MyCoolType");
      auto fetched = namedEulType.getLlvmType(&ctx);
      Assert::equals(namedLlvmType, fetched, t+"A1");
  }


  public: static void runAll() {
    Assert::warnNotTested("EulNamedTypeTest::castValue");
    namedTypeTest("EulNamedTypeTest.namedTypeTest ");
  }
};
