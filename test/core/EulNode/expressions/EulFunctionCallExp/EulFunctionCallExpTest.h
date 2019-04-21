#pragma once





class EulFunctionCallExpTest {
   public: static void valueTest(const std::string& t) {
     Compiler comp(0);
     llvm::LLVMContext llvmCtx;
     llvm::Module module("dummyName", llvmCtx);
     EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);
     comp.program.declareClibSymbols(&ctx);

     //1. Set an entry point
     llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
     llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
     ctx.builder.SetInsertPoint(block);


     //2. Setup a call expression
     EulFunctionCallExp tok(
         std::make_shared<EulSymbolNameNode>("exit", ctx.currentScope),
         std::make_shared<std::vector<std::shared_ptr<ValueNode>>>()
     );
     tok.params->push_back(std::make_shared<EulIntNode>(123,32,false));

     //3. Run it and check the result
     auto val = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
     Assert::that(val->getType()->isVoidTy(), t+"A1");

     Assert::equals(1, ctx.builder.GetInsertBlock()->size(), t+"B1");
     auto instruction = &(*ctx.builder.GetInsertBlock()->begin());
     Assert::that(llvm::CallInst::classof(instruction), t+"B2");

     auto asCallInst = static_cast<llvm::CallInst*>(instruction);
     Assert::that(asCallInst->getType()->isVoidTy(), t+"C1");
     Assert::equals(ctx.currentScope->get("exit")->llvmValue, asCallInst->getCalledFunction(), t+"C2");
     Assert::equals(1, asCallInst->getNumArgOperands(), t+"C3");
     Assert::llvmIntConstant(asCallInst->getArgOperand(0), 32, 123, t+"C4");


     //4. Test error cases: wrong argument list count
     tok.params->push_back(std::make_shared<EulIntNode>(123,32,false));
     try {
         tok.generateValue(&ctx, EulCodeGenFlags_NONE);
         Assert::fail(t+" Exception expected due to wrong argument list count, but none was thrown.");
     }
     catch(EulError e) {
         Assert::enumEquals(EulErrorType::NOT_IMPLEMENTED, e.type, t+"D1");
         Assert::equals("NOT_IMPLEMENTED wrong parameter list count.", e.message, t+"D2");
     }
   }


  public: static void runAll() {
    valueTest("EulFunctionCallExpTest.valueTest ");
  }
};
