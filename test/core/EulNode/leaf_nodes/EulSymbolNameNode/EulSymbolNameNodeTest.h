#pragma once





class EulSymbolNameNodeTest {

  public: static void constructorTest(const std::string& t) {
      auto scope = std::make_shared<EulScope>(nullptr);

      std::string str = "someName";
      EulSymbolNameNode tok = EulSymbolNameNode(str.c_str(), str.length(), scope);
      Assert::equals("someName", tok.name, t+"A1");
      Assert::equals(scope.get(), tok.scope.get(), t+"A1_scope");

      str = "someOtherName";
      EulSymbolNameNode tok2 = EulSymbolNameNode(str.c_str(), str.length(), scope);
      Assert::equals("someOtherName", tok2.name, t+"A2");
      Assert::equals(scope.get(), tok2.scope.get(), t+"A2_scope");

      //check that first token did not change
      Assert::equals("someName", tok.name, t+"A3");

      //check type getter
      Assert::enumEquals(EulNodeType::ID, tok.getNodeType(), t+"A4");
  }

  public: static void getEulType(const std::string& t) {
     Compiler comp(0);
     llvm::LLVMContext llvmCtx;
     llvm::Module module("dummyName", llvmCtx);
     EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

     //1. Declare a couple of symbols
     comp.program.globalScope->declare(
         "new1",
         std::make_shared<EulSymbol>(
             yy::EulParser::token::VAR,
             comp.program.nativeTypes.stringType,
             std::make_shared<EulStringNode>("123")
         )
     );
     comp.program.globalScope->declare(
         "new2",
         std::make_shared<EulSymbol>(
             yy::EulParser::token::VAR,
             comp.program.nativeTypes.float32Type,
             std::make_shared<EulFloatNode>(2.3, 32)
         )
     );

     //2. Get the type of the symbols
     EulSymbolNameNode tok("new1", comp.program.globalScope);
     auto eulType = tok.getEulType(&ctx, 0);
     Assert::equals(eulType.get(), comp.program.nativeTypes.stringType.get(), t+"A1");

     tok.name.assign("new2");
     eulType = tok.getEulType(&ctx, 0);
     Assert::equals(eulType.get(), comp.program.nativeTypes.float32Type.get(), t+"A2");

     tok.name.assign("Int32");
     eulType = tok.getEulType(&ctx, 0);
     Assert::null(eulType.get(), t+"B1");


     //3. Try accessing a non existing symbol
     try {
         tok.name.assign("iDoNotExist");
         eulType = tok.getEulType(&ctx, 0);
         Assert::fail(t+" Expected exception due to non existing symbol, but none was thrown.");
     }
     catch(EulError e) {
         Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"C1");
         Assert::equals("iDoNotExist: Symbol not found.", e.message, t+"C2");
     }
 }

 public: static void generateValue(const std::string& t) {
     Compiler comp(0);
     llvm::LLVMContext llvmCtx;
     llvm::Module module("dummyName", llvmCtx);
     EulCodeGenContext ctx(&comp, llvmCtx, &module, comp.program.globalScope, nullptr);

     //1. Set an entry point
     llvm::Function* mainFunc = (llvm::Function*)ctx.module->getOrInsertFunction("main", llvm::IntegerType::get(ctx.context, 32));
     llvm::BasicBlock *block = llvm::BasicBlock::Create(ctx.context, "entry", mainFunc);
     ctx.builder.SetInsertPoint(block);

     //2. Declare a couple of symbols
     auto symbol = std::make_shared<EulSymbol>(
         yy::EulParser::token::VAR,
         comp.program.nativeTypes.stringType,
         std::make_shared<EulIntNode>(123, 32, false)
     );
     symbol->llvmValue = ctx.builder.CreateAlloca(llvm::IntegerType::get(ctx.context, 32), nullptr, "someIntVar");
     auto store = ctx.builder.CreateStore(
         llvm::ConstantInt::get(llvm::IntegerType::get(ctx.context, 32), 123, true),
         symbol->llvmValue
     );
     comp.program.globalScope->declare("someIntVar", symbol);

     symbol = std::make_shared<EulSymbol>(
         yy::EulParser::token::VAR,
         comp.program.nativeTypes.float32Type,
         std::make_shared<EulFloatNode>(7.5, 32)
     );
     symbol->llvmValue = llvm::ConstantFP::get(comp.program.nativeTypes.float32Type->getLlvmType(&ctx), 7.5);
     comp.program.globalScope->declare("someFloatLiteral", symbol);

     //3. Get the type of the symbols
     EulSymbolNameNode tok("someFloatLiteral", comp.program.globalScope);
     auto llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
     Assert::llvmFloatConstant(llvmValue, 32, 7.5, 0.001, t+"A1");
     Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"A2"); //we start with 2 commands in the block: the alloca and the store.

     tok.name.assign("Int32");
     llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
     Assert::null(llvmValue, t+"B1");
     Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"B2");


     //4. Try accessing a non existing symbol
     try {
         tok.name.assign("iDoNotExist");
         llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_NONE);
         Assert::fail(t+" Expected exception due to non existing symbol, but none was thrown.");
     }
     catch(EulError e) {
         Assert::enumEquals(EulErrorType::SEMANTIC, e.type, t+"D1");
         Assert::equals("iDoNotExist: Symbol not found.", e.message, t+"D2");
         Assert::equals(2, ctx.builder.GetInsertBlock()->size(), t+"D3");
     }

     //5. Try again with EulCodeGenFlags_LOAD_VAR flags this should generate a load instruction
     tok.name.assign("someIntVar");
     llvmValue = tok.generateValue(&ctx, EulCodeGenFlags_LOAD_VAR);
     Assert::that(llvm::LoadInst::classof(llvmValue), t+"E1");

     auto asLoadInstr = static_cast<llvm::LoadInst*>(llvmValue);
     Assert::equals(3, ctx.builder.GetInsertBlock()->size(), t+"E3");
 }

  public: static void runAll() {
    constructorTest("EulSymbolNameNodeTest.constructorTest ");
    generateValue("EulSymbolNameNodeTest.generateValue ");
    getEulType("EulSymbolNameNodeTest.getEulType ");
  }
};
