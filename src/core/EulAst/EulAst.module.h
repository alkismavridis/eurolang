/** On this file, we will implement all methods from every header file on this "package". */
#pragma once

#include "EulAst.CodeGen.impl.h"
#include "./EulType/EulType.impl.h"




//region BASE CLASS
EulAstType EulAst::getAstType() { return NO_TYPE; }
EulTokenType EulAst::getType() { return AST; }
//endregion


//region VAR DECLARATION
VarDeclaration::VarDeclaration(std::shared_ptr<EulIdToken> id, std::shared_ptr<EulType> varType, std::shared_ptr<EulToken> value) {
    this->id = id;
    this->varType = varType;
    this->value = value;
}

EulAstType VarDeclaration::getAstType() { return PARAM_DECLARATION; }

void VarDeclaration::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\": \"VarDeclaration\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"id\":\"" <<  this->id->name << "\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->value!=nullptr) {
        out << "\"value\": ";
        this->value->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "\"value\": null" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->varType!=nullptr) {
        out << "\"varType\": ";
        this->varType->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "\"varType\": null" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
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
VarDeclarationStatement::VarDeclarationStatement(int varType, std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> declarations) {
    this->varType = varType;
    this->declarations = declarations;
}

EulStatementType VarDeclarationStatement::getStatementType() { return VAR_DECLARATION; }

void VarDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"VarDeclarationStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\":" <<  this->varType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"declarations\": TODO";
    //auto castedVector = std::static_pointer_cast<std::vector<std::shared_ptr<VarDeclaration>>>(this->declarations);
    //EulToken::toJson(out, *castedVector.get(), tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion


//region RETURN STATEMENT
ReturnStatement::ReturnStatement(std::shared_ptr<EulToken> exp) {
    this->exp = exp;
}

EulStatementType ReturnStatement::getStatementType() { return RETURN_STATEMENT; }

void ReturnStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"ReturnStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\": ";
    if (this->exp == nullptr) out << "null" << std::endl;
    else {
        this->exp->toJson(out, tabs);
        std::cout << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region EXPRESSION BASE
EulAstType EulExpression::getAstType() { return EXPRESSION; }
EulExpressionType EulExpression::getExpressionType() { return UNKNOWN_EXP; }
std::shared_ptr<EulType> EulExpression::getEulType(EulCodeGenContext* ctx, unsigned int someParam) { return this->compileTimeType; }
//endregion



//region PREFIX EXPRESSION
EulPrefixExp::EulPrefixExp(EulOperator* oper, std::shared_ptr<EulToken> exp) {
    this->exp = exp;
    this->oper = oper;
}

void EulPrefixExp::toJson(std::ostream& out, int tabs) {
   out << "{" << std::endl;
   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"type\":\"EulPrefixExp\"," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

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
EulInfixExp::EulInfixExp(std::shared_ptr<EulToken> left, EulOperator* oper, std::shared_ptr<EulToken> right) {
    this->left = left;
    this->oper = oper;
    this->right = right;
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
    out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

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
EulSuffixExp::EulSuffixExp(std::shared_ptr<EulToken> exp, EulOperator* oper) {
    this->exp = exp;
    this->oper = oper;
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
    out << "\"oper\":" << this->oper->getOperatorText() << "," << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulSuffixExp::getExpressionType() { return SUFFIX_EXP; }
//endregion



//region TOKEN EXPRESSION
EulTokenExp::EulTokenExp(std::shared_ptr<EulToken> token) { this->token = token; }

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




//region FUNCTION CALL EXPRESSION
EulFunctionCallExp::EulFunctionCallExp(std::shared_ptr<EulToken> func, std::shared_ptr<std::vector<std::shared_ptr<EulToken>>> params) {
    this->func = func;
    this->params = params;
}

void EulFunctionCallExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunctionCallExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"func\":";
    this->func->toJson(out, tabs+1);
    out << std::endl;


    //print parameters
    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->params == nullptr) out << "\"params\": null" << std::endl;
    else {
        out << "\"params\": [" << std::endl;

        //print one parameter in each loop step
        for (auto p : *this->params) {
            for (int i=tabs+1; i>=0; --i) out << "\t";
            p->toJson(out, tabs+2);
            out << "," << std::endl; //TODO last entry should be without comma
        }
        for (int i=tabs; i>=0; --i) out << "\t";
        out << "]" << std::endl;
    }

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulFunctionCallExp::getExpressionType() { return FUNCTION_CALL; }
//endregion




//region FUNCTION CALL EXPRESSION
EulArrayAccessExp::EulArrayAccessExp(std::shared_ptr<EulToken> obj, std::shared_ptr<EulToken> index) {
    this->obj = obj;
    this->index = index;
}

void EulArrayAccessExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulArrayAccessExp\"," << std::endl;


    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"obj\":";
    this->obj->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"index\":";
    this->index->toJson(out, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulArrayAccessExp::getExpressionType() { return ARRAY_ACCESS; }
//endregion



//region EUL EXPRESSION STATEMENT
EulExpStatement::EulExpStatement(std::shared_ptr<EulToken> exp) {
    this->exp = exp;
}

void EulExpStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulExpStatement\"," << std::endl;


    //print value
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\": ";
    if (this->exp != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->exp->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "null" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulStatementType EulExpStatement::getStatementType() { return EulStatementType::EXPRESSION_STATEMENT; }
//endregion
