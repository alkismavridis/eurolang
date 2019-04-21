#pragma once





class EulInfixExpTest {


  public: static void eulInfixExpValueTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Set an entry point
      llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
      llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
      ctx.builder.SetInsertPoint(block);

      //2. Create an infix expression
      EulInfixExp tok(
          std::make_shared<EulIntNode>(123, 32, false),
          &EUL_OPERATORS.plusOperator,
          std::make_shared<EulIntNode>(153, 64, false)
      );

      //3. Run in and see the result
      auto value = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(value, 64, 276, t+"A1");
  }


  public: static void assignmentInfixExpValueTest(const std::string& t) {
      Compiler comp(0);
      llvm::LLVMContext llvmCtx;
      llvm::Module module("dummyName", llvmCtx);
      EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

      //1. Make an entry point
      llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
      llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
      ctx.builder.SetInsertPoint(block);

      //2. Create a var declaration (Int32), and insert it into the scope
      VarDeclarationStatement declaration(yy::EulParser::token::VAR, std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>());
      declaration.declarations->push_back(
          std::make_shared<VarDeclaration>(
              std::make_shared<EulSymbolNameNode>("myVar", ctx.currentScope),
              nullptr,
              std::make_shared<EulIntNode>(123, 32, false)
          )
      );
      ctx.currentScope->declare(&declaration);
      declaration.generateStatement(&ctx);

      //3.Create an assignment expression
      EulInfixExp tok(
          std::make_shared<EulSymbolNameNode>("myVar", ctx.currentScope),
          &EUL_OPERATORS.assignOperator,
          std::make_shared<EulIntNode>(999, 64, false)
      );

      //4. Generate the llvm statement and assert it
      auto result = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
      Assert::llvmIntConstant(result, 64, 999, t+"A1 result of assignment is the right operand");

      auto instruction = &ctx.builder.GetInsertBlock()->back(); //get the last instruction
      Assert::that(llvm::StoreInst::classof(instruction), t+"A1 is store instruction");
      auto asStoreInst = static_cast<llvm::StoreInst*>(instruction);
      Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"A2 produces an Int32");
      Assert::llvmIntConstant(asStoreInst->getValueOperand(), 32, 999, t+"A3");
      Assert::equals(ctx.currentScope->get("myVar")->llvmValue, asStoreInst->getPointerOperand(), t+"A4 value is assigned to myVar");
      Assert::equals(comp.program.nativeTypes.int32Type.get(), tok.compileTimeType.get(), t+"A5 result type");
  }


  public: static void runAll() {
    eulInfixExpValueTest("EulInfixExpTest.eulInfixExpValueTest ");
    assignmentInfixExpValueTest("EulInfixExpTest.assignmentInfixExpValueTest ");
  }
};
