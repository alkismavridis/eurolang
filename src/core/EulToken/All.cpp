/** On this file, we will implement all methods from every header file on this "package". */

#include <string>
#include <forward_list>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>


#include "../../constants/Constants.h"
#include "EulTokenType.h"
#include "EulToken.h"
#include "EulCharToken.h"
#include "EulFloatToken.h"
#include "EulIdToken.h"
#include "EulIntToken.h"
#include "EulStringToken.h"


#include "../EulAst/EulAstType.h"
#include "../EulAst/EulAst.h"

#include "../EulAst/EulDeclaration/VarDeclaration.h"


#include "../EulAst/EulStatement/EulStatementType.h"
#include "../EulAst/EulStatement/EulStatement.h"
#include "../EulAst/EulStatement/EulImportStatement.h"
#include "../EulAst/EulStatement/EulExportStatement.h"


#include "../EulSourceFile/EulSourceFile.h"
#include "../EulProgram/EulProgram.h"
#include "../Compiler/Compiler.h"



//region BASE CLASS
EulToken::~EulToken() {}
EulTokenType EulToken::getType() { return UNKNOWN; }

void EulToken::toJson(std::ostream& out, int tabs) {
    out << "{\"type\":\"EulToken\"}" << std::endl;
}


std::ostream& operator<<(std::ostream& os, EulToken* tok) {
    tok->toJson(os, 0);
    return os;
}
//endregion




//region CHAR TOKEN
EulCharToken::EulCharToken(unsigned long int value, unsigned char size) {
    this->value = value;
    this->size = size;
}

EulCharToken::EulCharToken(const char* text, unsigned int len, Compiler* compiler) {
    this->size = len - 2; //we default the char size to its UTF length. We substract 2, because there are the '' quotes.

    switch(len) {
        case 3: //1 byte unicode
            this->value = (unsigned char) ( *(text+1) );
            break;

        case 4: //2 byte unicode
            this->value = ((unsigned char)text[1])<<8 | (unsigned char)text[2];
            break;

        case 6: //4 byte unicode
            this->value = (unsigned char)text[1];
            this->value = (this->value << 8) | (unsigned char)text[2];
            this->value = (this->value << 8) | (unsigned char)text[3];
            this->value = (this->value << 8) | (unsigned char)text[4];
            break;

        default:
            compiler->makeLexerError("Invalid char size");
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
    out << "\"value\":" <<  this->value << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region ID VALUE
EulIdToken::EulIdToken(const char* text, unsigned int length) {
    this->name.assign(text, length);
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
EulIntToken::EulIntToken(char* text) {
    this->value = strtoul(text, &text, 10);		//setup value
    if (*text) { //setup signed or unsigned flag
        this->isUnsigned = (*text) == 'u';
        text++;
    }
    else this->isUnsigned = 0; //default is signed

    if (*text) this->size = strtoul(text, &text, 10);	//setup size, if any
    else this->size = EUL_LANG_DEFAULT_INT_SIZE;
}

EulTokenType EulIntToken::getType() { return INT; }


void EulIntToken::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulIntToken\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\":" <<  this->value << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion



//region STRING VALUE
EulStringToken::EulStringToken(std::string& buf) {
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