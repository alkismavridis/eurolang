#pragma once

llvm::Value* EulToken::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulToken" << std::endl;
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateValue was called, but should not!");
}

llvm::Type* EulToken::generateType(EulCodeGenContext* ctx) {
    std::cout << "EulToken" << std::endl;
    throw EulError(EulErrorType::SEMANTIC, "EulToken::generateType was called, but should not!");
}



//CHAR
llvm::Value* EulCharToken::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulCharToken" << std::endl;

    //TODO char literals. At the moment we return an Int
    //return llvm::ConstantChar::get(ctx->context, llvm::APCharLiteral(this->size, this->value, false));
    return nullptr;
}

llvm::Type* EulCharToken::generateType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size); //TODO signed or unsigned?
}



//FLOAT
llvm::Value* EulFloatToken::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulFloatToken" << std::endl;

    //TODO Size?
    return llvm::ConstantFP::get(ctx->context, llvm::APFloat(this->value));
}

llvm::Type* EulFloatToken::generateType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size); //TODO signed or unsigned?
}



//ID
llvm::Value* EulIdToken::generateValue(EulCodeGenContext* ctx) {
    //TODO ids can be many different things. Probably only the AST will know what we really are...
    std::cout << "EulIdToken" << std::endl;

    //return ctx->builder->CreateLoad();

    //1. find the symbol in scope
    std::shared_ptr<EulSymbol> sym = this->scope->get(this->name);
    if (sym==nullptr) throw EulError(EulErrorType::SEMANTIC, "Symbol with name "+ this->name +" not found.");

    auto loadInstr = ctx->builder.CreateLoad(
        llvm::IntegerType::get(ctx->context, 32), //TODO give the correct type.
        sym->allocInstruction
    );

    return loadInstr;
}


//INT
llvm::Value* EulIntToken::generateValue(EulCodeGenContext* ctx) {
    return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, !this->isUnsigned));
}


llvm::Type* EulIntToken::generateType(EulCodeGenContext* ctx) {
    return llvm::IntegerType::get(ctx->context, this->size); //TODO signed or unsigned?
}


//STRING
llvm::Value* EulStringToken::generateValue(EulCodeGenContext* ctx) {
    std::cout << "EulStringToken" << std::endl;

    //TODO create string literal
    return nullptr;
}