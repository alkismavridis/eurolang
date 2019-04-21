#pragma once





class EulExpStatementTest {


  public: static void eulExpStatementValueTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);
      comp.program.declareClibSymbols(&ctx);

      //1. Set an entry point
      llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
      llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
      ctx.builder.SetInsertPoint(block);


      //2. Create an operation (like a binary one), and insert it into an EulExpStatement
      auto funcCallExp = std::make_shared<EulFunctionCallExp>(
          std::make_shared<EulSymbolNameNode>("exit", ctx.currentScope),
          std::make_shared<std::vector<std::shared_ptr<ValueNode>>>()
      );
      funcCallExp->params->push_back(std::make_shared<EulIntNode>(123,32,false));
      EulExpStatement tok(funcCallExp);

      //3. Execute the expression and check result
      tok.generateStatement(&ctx);
      Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"A1");


      //4. Check that unreachable statements are not allowed
      ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
      try {
          tok.generateStatement(&ctx);
          Assert::fail(t+"Exception expected due to unreachable expression statement, But none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"A2");
          Assert::equals("Unreachable statement.", e.message, t+"A3");
      }
  }


  public: static void runAll() {
    eulExpStatementValueTest("EulExpStatementTest.eulExpStatementValueTest ");
  }
};
