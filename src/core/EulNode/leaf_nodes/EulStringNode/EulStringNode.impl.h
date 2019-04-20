#pragma once


//region LIFE CYCLE
EulStringNode::EulStringNode(const std::string& buf) {
    this->value.assign(buf);
}
//endregion


//region CORE FUNCTIONS
EulNodeType EulStringNode::getNodeType() { return EulNodeType::STRING; }
bool EulStringNode::isSymbolId() { return false; }
//endregion


//region CODE GENERATION
llvm::Value* EulStringNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    //0. Defs
    auto str = this->value;
    auto charType = llvm::IntegerType::get(ctx->context, 8);


    //1. Initialize chars vector
    std::vector<llvm::Constant *> chars(str.length());
    for(unsigned int i = 0; i < str.size(); i++) {
      chars[i] = llvm::ConstantInt::get(charType, str[i]);
    }

    //1b. add a zero terminator too
    chars.push_back(llvm::ConstantInt::get(charType, 0));


    //2. Initialize the string from the characters
    auto stringType = llvm::ArrayType::get(charType, chars.size());

    //3. Insert the constant into the module
    auto globalDeclaration = ctx->makeGlobalLiteral(stringType);
    globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
    globalDeclaration->setConstant(true);
    globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
    globalDeclaration->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);


    //3. Return a cast to an i8*
    return llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
}

std::shared_ptr<EulType> EulStringNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    return ctx->compiler->program.nativeTypes.stringType;
}
//endregion



//region SERIALIZATION
void EulStringNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulStringNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":\"" <<  this->value << "\"" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
