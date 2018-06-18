/** On this file, we will implement all methods from every header file on this "package". */

#include <string>
#include <forward_list>
#include <vector>
#include <sstream>
#include <map>
#include <iostream>


#include "../../constants/Constants.h"
#include "../EulToken/EulTokenType.h"
#include "../EulToken/EulToken.h"
#include "../EulToken/EulCharToken.h"
#include "../EulToken/EulFloatToken.h"
#include "../EulToken/EulIdToken.h"
#include "../EulToken/EulIntToken.h"
#include "../EulToken/EulStringToken.h"

#include "EulAstType.h"
#include "EulAst.h"

#include "EulDeclaration/VarDeclaration.h"

#include "EulStatement/EulStatementType.h"
#include "EulStatement/EulStatement.h"
#include "EulStatement/EulImportStatement.h"
#include "EulStatement/EulExportStatement.h"
#include "EulStatement/VarDeclarationStatement.h"

#include "EulExpression/EulExpressionType.h"
#include "EulExpression/EulExpression.h"
#include "EulExpression/EulInfixExp.h"
#include "EulExpression/EulPrefixExp.h"
#include "EulExpression/EulSuffixExp.h"
#include "EulExpression/EulTokenExp.h"




//region BASE CLASS
EulAstType EulAst::getAstType() { return NO_TYPE; }
EulTokenType EulAst::getType() { return AST; }
//endregion


//region VAR DECLARATION
VarDeclaration::VarDeclaration(EulIdToken* id, EulToken* value) {
    this->id = id;
    this->value = value;
}

VarDeclaration::~VarDeclaration() {
    delete this->id;
    delete this->value;
}

EulAstType VarDeclaration::getAstType() { return PARAM_DECLARATION; }

void VarDeclaration::toJson(std::ostream& out, int tabs) {
    out << "Unknown token" << std::endl;
}
//endregion



//region STATEMENT BASE
EulStatementType EulStatement::getStatementType() { return UNKNOWN_STATEMENT; }
EulAstType EulStatement::getAstType() { return STATEMENT; }
//endregion



//region IMPORT STATEMENT
EulStatementType EulImportStatement::getStatementType() { return IMPORT; }

void EulImportStatement::toJson(std::ostream& out, int tabs) {
    out << "Unknown token" << std::endl;
}
//endregion



//region EXPORT STATEMENT
EulStatementType EulExportStatement::getStatementType() { return EXPORT; }

void EulExportStatement::toJson(std::ostream& out, int tabs) {
    out << "EulExportStatement" << std::endl;
}
//endregion



//region VARIABLE DECLARATION STATEMENT
VarDeclarationStatement::VarDeclarationStatement(int varType, std::vector<VarDeclaration*>* declarations) {
    this->varType = varType;
    this->declarations = declarations;
}

VarDeclarationStatement::~VarDeclarationStatement() {
    if (this->declarations != nullptr) {
        for (auto d : *this->declarations) delete d;
        delete this->declarations;
    }
}

EulStatementType VarDeclarationStatement::getStatementType() { return VAR_DECLARATION; }

void VarDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "VarDeclarationStatement" << std::endl;
}
//endregion




//region EXPRESSION BASE
EulAstType EulExpression::getAstType() { return EXPRESSION; }
EulExpressionType EulExpression::getExpressionType() { return UNKNOWN_EXP; }
//endregion



//region PREFIX EXPRESSION
EulPrefixExp::EulPrefixExp(int operatorType, EulToken* exp) {
    this->exp = exp;
    this->operatorType = operatorType;
}

EulPrefixExp::~EulPrefixExp() {
    delete this->exp;
}

void EulPrefixExp::toJson(std::ostream& out, int tabs) {
   out << "{" << std::endl;
   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"type\":\"EulPrefixExp\"," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"operatorType\":" << this->operatorType << "," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"exp\":";
   this->exp->toJson(out, tabs+1);
   out << std::endl;

   for (int i=tabs-1; i>=0; --i) out << "\t";
   out << "}";
}

EulExpressionType EulPrefixExp::getExpressionType() { return PREFIX_EXP; }
//endregion




//region INFIX EXPRESSION
EulInfixExp::EulInfixExp(EulToken* left, int operatorType, EulToken* right) {
    this->left = left;
    this->operatorType = operatorType;
    this->right = right;
}

EulInfixExp::~EulInfixExp() {
    delete this->left;
    delete this->right;
}

void EulInfixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulInfixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"left\":";
    this->left->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"operatorType\":" << this->operatorType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"right\":";
    this->right->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulInfixExp::getExpressionType() { return INFIX_EXP; }
//endregion



//region SUFFIX EXPRESSION
EulSuffixExp::EulSuffixExp(EulToken* exp, int operatorType) {
    this->exp = exp;
    this->operatorType = operatorType;
}

EulSuffixExp::~EulSuffixExp() {
    delete this->exp;
}

void EulSuffixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSuffixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\":";
    this->exp->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"operatorType\":" << this->operatorType << "," << std::endl;



    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulSuffixExp::getExpressionType() { return SUFFIX_EXP; }
//endregion



//region TOKEN EXPRESSION
EulTokenExp::EulTokenExp(EulToken* token) { this->token = token; }
EulTokenExp::~EulTokenExp() { delete this->token; }

void EulTokenExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulTokenExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"token\":";
    this->token->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulTokenExp::getExpressionType() { return TOKEN; }

//endregion