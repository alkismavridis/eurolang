/** On this file, we will implement all methods from every header file on this "package". */

#pragma once


#include "EulToken.CodeGen.impl.h"


//region BASE CLASS
EulToken::~EulToken() {}
EulTokenType EulToken::getType() { return UNKNOWN; }

void EulToken::toJson(std::ostream& out, int tabs) {
    out << "{\"type\":\"EulToken\"}";
}


std::ostream& operator<<(std::ostream& os, EulToken* tok) {
    tok->toJson(os, 0);
    return os;
}

void EulToken::toJson(std::ostream& out, std::vector<EulToken*>* tokens, int tabs) {
    out << "[" << std::endl;

    for (auto const& t : *tokens) {
        for (int i=tabs; i>=0; --i) out << "\t";

        if (t!=nullptr) t->toJson(out, tabs+1);
        else out << "null";

        out << "," << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "]";
}

void EulToken::toJson(std::ostream& out, std::vector<std::shared_ptr<EulToken>> tokens, int tabs) {
    out << "[" << std::endl;

    for (auto const& t : tokens) {
        for (int i=tabs; i>=0; --i) out << "\t";

        if (t!=nullptr) t->toJson(out, tabs+1);
        else out << "null";

        out << "," << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "]";
}
//endregion




//region CHAR TOKEN
EulCharToken::EulCharToken(unsigned long int value, unsigned char size) {
    this->value = value;
    this->size = size;
}

EulCharToken::EulCharToken(const char* text, unsigned int len, Compiler* compiler) {
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


EulTokenType EulCharToken::getType() { return CHAR; }

void EulCharToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCharToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":'" <<  this->value << "'" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region FLOAT VALUE
EulFloatToken::EulFloatToken(double value, unsigned char size) {
    this->value = value;
    this->size = size;
}


EulFloatToken::EulFloatToken(char* text) {
    this->value = strtod(text, &text);
    if (*text == 'f') text++; //skip f character, if any

    if (*text) this->size = strtoul(text, &text, 10);
    else this->size = EUL_LANG_DEFAULT_FLOAT_SIZE;
}



EulTokenType EulFloatToken::getType() { return FLOAT; }

void EulFloatToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFloatToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\": " <<  this->value << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region ID VALUE
EulIdToken::EulIdToken(const char* text, unsigned int length, std::shared_ptr<EulScope> scope) {
    this->name.assign(text, length);
    this->scope = scope;
}

EulIdToken::EulIdToken(const std::string& name, std::shared_ptr<EulScope> scope) {
    this->name = name;
    this->scope = scope;
}

EulTokenType EulIdToken::getType() { return ID; }

void EulIdToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIdToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"name\":\"" <<  this->name << "\"" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region INT TOKEN
EulIntToken::EulIntToken(unsigned long int value, unsigned char size, bool isUnsigned) {
    this->value = value;
    this->size = size;
    this->isUnsigned = isUnsigned;
}

EulIntToken::EulIntToken(char* text) {
    this->value = strtoul(text, &text, 10);		//setup value
    if (*text) { //setup signed or unsigned flag
        this->isUnsigned = (*text) == 'u';
        text++;
    }
    else this->isUnsigned = false; //default is signed

    if (*text) this->size = strtoul(text, &text, 10);	//setup size, if any
    else this->size = EUL_LANG_DEFAULT_INT_SIZE;
}

EulTokenType EulIntToken::getType() { return INT; }


void EulIntToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIntToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":" <<  this->value << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"size\":" <<  (int) this->size << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"isUnsigned\": " <<  (int) this->isUnsigned << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion



//region BOOLEAN VALUE
EulBooleanToken::EulBooleanToken(bool value) {
    this->value = value;
}


EulTokenType EulBooleanToken::getType() { return BOOLEAN; }

void EulBooleanToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulBooleanToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->value) out << "\"value\": true" << std::endl;
    else out << "\"value\": false" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion



//region STRING VALUE
EulStringToken::EulStringToken(const std::string& buf) {
    this->value.assign(buf);
}


EulTokenType EulStringToken::getType() { return STRING; }

void EulStringToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulStringToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":\"" <<  this->value << "\"" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion