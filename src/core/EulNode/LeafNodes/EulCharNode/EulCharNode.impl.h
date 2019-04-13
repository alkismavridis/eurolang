#pragma once


//region LIFE CYCLE
EulCharNode::EulCharNode(unsigned long int value, unsigned char size) {
    this->value = value;
    this->size = size;
}

EulCharNode::EulCharNode(const char* text, unsigned int len, Compiler* compiler) {
    switch(len) {
        case 3: //1 byte unicode
            this->size = 8;
            this->value = (unsigned char) ( *(text+1) );
            break;

        case 4: //2 byte unicode
            this->size = 16;
            this->value = ((unsigned char)text[1])<<8 | (unsigned char)text[2];
            break;

        case 6: //4 byte unicode
            this->size = 32;
            this->value = (unsigned char)text[1];
            this->value = (this->value << 8) | (unsigned char)text[2];
            this->value = (this->value << 8) | (unsigned char)text[3];
            this->value = (this->value << 8) | (unsigned char)text[4];
            break;

        default:
            compiler->addError(EulErrorType::LEXER, "Invalid char size");
            return;
    }
}
//endregion



//region CORE
EulTokenType EulCharNode::getType() { return EulTokenType::CHAR; }
//endregion



//region CODE GENERATION
llvm::Value* EulCharNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    switch(this->size) {
        case 8:
        case 16:
        case 32: return llvm::ConstantInt::get(ctx->context, llvm::APInt(this->size, this->value, false));
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32.");
    }
}

std::shared_ptr<EulType> EulCharNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    switch(this->size) {
        case 8: return ctx->compiler->program.nativeTypes.char8Type;
        case 16: return ctx->compiler->program.nativeTypes.char16Type;
        case 32: return ctx->compiler->program.nativeTypes.char32Type;
        default: throw EulError(EulErrorType::SEMANTIC, "Invalid character size: " + std::to_string(this->size)+". Please use one of 8, 16, 32.");
    }
}
//endregion



//region SERIALIZATION
void EulCharNode::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCharNode\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":'" <<  this->value << "'" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
