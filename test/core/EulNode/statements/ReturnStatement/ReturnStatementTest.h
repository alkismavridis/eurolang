#pragma once





class ReturnStatementTest {
  public: static void generateStatement(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);
      comp.program.declareClibSymbols(&ctx);

      //1. Set an entry point
      ctx.currentFunction = comp.program.makeMain(&ctx);

      //2. Create an operation (like a binary one), and insert it into an EulExpStatement
      ReturnStatement tok(std::make_shared<EulIntNode>(123,32,false));

      //3. Execute the expression and check result
      tok.generateStatement(&ctx);
      Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"A1");

      auto instruction = &(*ctx.builder.GetInsertBlock()->begin());
      Assert::that(llvm::ReturnInst::classof(instruction), t+"A2");

      auto asRetInst = static_cast<llvm::ReturnInst*>(instruction);
      Assert::llvmIntConstant(asRetInst->getReturnValue(), 32, 123, t+"A3");

      //4. Check that unreachable statements are not allowed
      ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
      try {
          tok.generateStatement(&ctx);
          Assert::fail(t+"Exception expected due to unreachable expression statement, but none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"B1");
          Assert::equals("Unreachable statement.", e.message, t+"B2");
      }
  }

  public: static void runAll() {
    generateStatement("ReturnStatementTest.generateStatement ");
  }
};
