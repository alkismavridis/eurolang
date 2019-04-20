#pragma once


//region LIFE CYCLE
EulFuncDeclarationStatement::EulFuncDeclarationStatement(std::shared_ptr<EulFunction> func, std::shared_ptr<EulSymbolNameNode> name) {
    this->func = func;
    this->name = name;
    this->llvmFunc = nullptr;
}
//endregion



//region CORE FUNCTIONS
EulStatementType EulFuncDeclarationStatement::getStatementType() { return EulStatementType::FUNC_DECLARATION_STATEMENT; }
//endregion



//region CODE GENERATION
void EulFuncDeclarationStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    //1. Save the current state to restore later.
    auto blockToReturnTo = ctx->builder.GetInsertBlock();
    auto functionToReturnTo = ctx->currentFunction;

    //2. Prepare the block
    auto eulBlock = this->func->block;
    ctx->currentScope = eulBlock->scope;
    llvm::BasicBlock *basicBlock = llvm::BasicBlock::Create(ctx->context, "entry", this->llvmFunc);
    ctx->currentFunction = this->func;
    ctx->builder.SetInsertPoint(basicBlock);


    //3. Create the parameters, if any exist
    auto params = this->func->parameters;
    if (params != nullptr) {
        auto argIterator = this->llvmFunc->arg_begin();
        for (auto& paramDecl : *params) {
            auto symbol = ctx->currentScope->get(paramDecl->id->name);
            auto allocInst = ctx->builder.CreateAlloca(paramDecl->varType->getLlvmType(ctx), nullptr, paramDecl->id->name);
            ctx->builder.CreateStore(&(*argIterator), allocInst);
            symbol->llvmValue = allocInst;
            argIterator++;
        }
    }

    //4. Generate the function statements
    eulBlock->generateStatements(ctx);


    //5. Finally, handle possible non terminated blocks
    if ( ctx->builder.GetInsertBlock()->getTerminator()==nullptr) {
        if (this->func->functionType->retType == ctx->compiler->program.nativeTypes.voidType) {
            ctx->builder.CreateRet(nullptr);
        }
        else throw EulError(EulErrorType::SEMANTIC, "Missing return statement from a non void function: " + this->name->name);
    }


    //6. Restore all needed variables in order to continue
    ctx->builder.SetInsertPoint(blockToReturnTo);
    ctx->currentScope = ctx->currentScope->superScope;
    ctx->currentFunction = functionToReturnTo;
}

void EulFuncDeclarationStatement::performPreParsing(EulCodeGenContext* ctx) {
    //1. Declare the function in llvm
    this->llvmFunc = llvm::Function::Create(
        static_cast<llvm::FunctionType*>(this->func->functionType->getLlvmType(ctx)),
        llvm::Function::CommonLinkage, //TODO maybe make some more research about that one...
        this->name->name,
        ctx->module
    );

    //2. Store the llvmFunc in the variable
    ctx->currentScope->get(this->name->name)->llvmValue = this->llvmFunc;
}
//endregion



//region SERIALIZATION
void EulFuncDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFuncDeclarationStatement TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
