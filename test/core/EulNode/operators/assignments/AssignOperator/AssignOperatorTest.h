#pragma once





class AssignOperatorTest {
  public: static void assignOperatorTest(const std::string& t) {
     Compiler comp(0);
     llvm::LLVMContext llvmCtx;
     llvm::Module module("dummyName", llvmCtx);
     EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

     //1. Make an entry point
     llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
     llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
     ctx.builder.SetInsertPoint(block);

     //2. Create a var declaration (Int32), and insert it into the scope
     VarDeclarationStatement tok(yy::EulParser::token::VAR, std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>());
     tok.declarations->push_back(
         std::make_shared<VarDeclaration>(
             std::make_shared<EulSymbolNameNode>("myVar", ctx.currentScope),
             nullptr,
             std::make_shared<EulIntNode>(123, 32, false)
         )
     );
     ctx.currentScope->declare(&tok);
     tok.generateStatement(&ctx);

     //3. Assign a new value to it (an Int64)
     std::shared_ptr<EulType> resultType;
     auto result = EUL_OPERATORS.assignOperator.assignInfix(
         ctx.currentScope->get("myVar").get(),
         llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 64), 999, true),
         comp.program.nativeTypes.int64Type,
         &resultType,
         &ctx
     );
     Assert::llvmIntConstant(result, 64, 999, t+"A1 result of assignment is the right operand");

     auto instruction = &ctx.builder.GetInsertBlock()->back(); //get the last instruction
     Assert::that(llvm::StoreInst::classof(instruction), t+"A1 is store instruction");
     auto asStoreInst = static_cast<llvm::StoreInst*>(instruction);
     Assert::equals(comp.program.nativeTypes.int32Type->getLlvmType(&ctx), asStoreInst->getValueOperand()->getType(), t+"A2 produces an Int32");
     Assert::llvmIntConstant(asStoreInst->getValueOperand(), 32, 999, t+"A3");
     Assert::equals(ctx.currentScope->get("myVar")->llvmValue, asStoreInst->getPointerOperand(), t+"A4 value is assigned to myVar");
     Assert::equals(comp.program.nativeTypes.int32Type.get(), resultType.get(), t+"A5 result type");


     Assert::warnNotTested("AssignOperatorTest.assignOperatorTest -- test multiple assignment expressions like x = y = 10");
  }


  public: static void runAll() {
    assignOperatorTest("AssignOperatorTest.assignOperatorTest ");
  }
};
