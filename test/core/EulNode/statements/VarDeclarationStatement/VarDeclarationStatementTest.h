#pragma once





class VarDeclarationStatementTest {
  public: static void generateStatement(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Set an entry point
      llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
      llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
      ctx.builder.SetInsertPoint(block);

      //2. Create a var declaration with two variables: one will have a value, the second not.
      VarDeclarationStatement tok(yy::EulParser::token::VAR, std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>());

      tok.declarations->push_back(
          std::make_shared<VarDeclaration>(
              std::make_shared<EulSymbolNameNode>("first", ctx.currentScope),
              nullptr,
              std::make_shared<EulIntNode>(123, 32, false)
          )
      );
      tok.declarations->push_back(
          std::make_shared<VarDeclaration>(
              std::make_shared<EulSymbolNameNode>("second", ctx.currentScope),
              comp.program.nativeTypes.float64Type,
              nullptr
          )
      );

      //declare them into the scope, too (important)
      ctx.currentScope->declare(&tok);

      //3. Generate the statement
      tok.generateStatement(&ctx);


      //4. Assert the resulted instructions
      Assert::equals(4, ctx.builder.GetInsertBlock()->size(), t+"A1");

      //4a. alloca instruction for first
      auto it = ctx.builder.GetInsertBlock()->begin();
      llvm::Instruction* instruction = &(*it);
      Assert::that(llvm::AllocaInst::classof(instruction), t+"B1");
      auto asAllocaInst = static_cast<llvm::AllocaInst*>(instruction);
      Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asAllocaInst->getAllocatedType(), t+"B2");

      //4b. store instruction for first
      it++;
      instruction = &(*it);
      Assert::that(llvm::StoreInst::classof(instruction), t+"C1");
      auto asStoreInst = static_cast<llvm::StoreInst*>(instruction);
      Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"C2");
      Assert::llvmIntConstant(asStoreInst->getValueOperand(), 32, 123, t+"C3");
      Assert::equals(asAllocaInst, asStoreInst->getPointerOperand(), t+"C4");

      //4c. alloca instruction for second
      it++;
      instruction = &(*it);
      Assert::that(llvm::AllocaInst::classof(instruction), t+"D1");
      asAllocaInst = static_cast<llvm::AllocaInst*>(instruction);
      Assert::equals(comp.program.nativeTypes.float64Type->getLlvmType(&ctx), asAllocaInst->getAllocatedType(), t+"D2");

      //4d. store instruction for second
      it++;
      instruction = &(*it);
      Assert::that(llvm::StoreInst::classof(instruction), t+"E1");
      asStoreInst = static_cast<llvm::StoreInst*>(instruction);
      Assert::equals(comp.program.nativeTypes.float64Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"E2");
      Assert::that(llvm::UndefValue::classof(asStoreInst->getValueOperand()), t+"E3");
      Assert::equals(asAllocaInst, asStoreInst->getPointerOperand(), t+"E4");

      //5. Check that unreachable statements are not allowed
      ctx.builder.CreateRet(llvm::ConstantInt::get(llvm::IntegerType::get(llvmCtx, 32), 0, true));
      try {
          tok.generateStatement(&ctx);
          Assert::fail(t+"Exception expected due to unreachable expression statement, But none was thrown.");
      }
      catch(EulError e) {
          Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"F1");
          Assert::equals("Unreachable statement.", e.message, t+"F2");
      }
  }


  public: static void runAll() {
    generateStatement("VarDeclarationStatementTest.generateStatement ");
  }
};
