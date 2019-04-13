/** On this file, we will implement all methods from every header file on this "package". */
#pragma once

#include "EulAst.CodeGen.impl.h"
#include "./EulType/EulType.impl.h"
#include "./EulType/EulType.CodeGen.impl.h"




//region BASE CLASS
EulAstType EulAst::getAstType() { return EulAstType::NO_TYPE; }
EulTokenType EulAst::getType() { return EulTokenType::AST; }
//endregion


//region VAR DECLARATION
VarDeclaration::VarDeclaration(std::shared_ptr<EulSymbolNameNode> id, std::shared_ptr<EulType> varType, std::shared_ptr<EulNode> value) {
    this->id = id;
    this->varType = varType;
    this->value = value;
}

EulAstType VarDeclaration::getAstType() { return EulAstType::PARAM_DECLARATION; }

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
EulStatementType EulStatement::getStatementType() { return EulStatementType::UNKNOWN_STATEMENT; }
EulAstType EulStatement::getAstType() { return EulAstType::STATEMENT; }
void EulStatement::performPreParsing(EulCodeGenContext* ctx) {}
//endregion



//region IMPORT STATEMENT
EulStatementType EulImportStatement::getStatementType() { return EulStatementType::IMPORT; }

void EulImportStatement::toJson(std::ostream& out, int tabs) {
    out << "Unknown token" << std::endl;
}
//endregion



//region EXPORT STATEMENT
EulStatementType EulExportStatement::getStatementType() { return EulStatementType::EXPORT; }

void EulExportStatement::toJson(std::ostream& out, int tabs) {
    out << "EulExportStatement" << std::endl;
}
//endregion



//region VARIABLE DECLARATION STATEMENT
VarDeclarationStatement::VarDeclarationStatement(int varType, std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> declarations) {
    this->varType = varType;
    this->declarations = declarations;
}

EulStatementType VarDeclarationStatement::getStatementType() { return EulStatementType::VAR_DECLARATION; }

void VarDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"VarDeclarationStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\":" <<  this->varType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"declarations\": TODO";
    //auto castedVector = std::static_pointer_cast<std::vector<std::shared_ptr<VarDeclaration>>>(this->declarations);
    //EulNode::toJson(out, *castedVector.get(), tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion


//region RETURN STATEMENT
ReturnStatement::ReturnStatement(std::shared_ptr<EulNode> exp) {
    this->exp = exp;
}

EulStatementType ReturnStatement::getStatementType() { return EulStatementType::RETURN_STATEMENT; }

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
EulAstType EulExpression::getAstType() { return EulAstType::EXPRESSION; }
EulExpressionType EulExpression::getExpressionType() { return EulExpressionType::UNKNOWN_EXP; }
std::shared_ptr<EulType> EulExpression::getEulType(EulCodeGenContext* ctx, unsigned int someParam) { return this->compileTimeType; }
//endregion



//region PREFIX EXPRESSION
EulPrefixExp::EulPrefixExp(EulOperator* oper, std::shared_ptr<EulNode> exp) {
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

EulExpressionType EulPrefixExp::getExpressionType() { return EulExpressionType::PREFIX_EXP; }
//endregion




//region INFIX EXPRESSION
EulInfixExp::EulInfixExp(std::shared_ptr<EulNode> left, EulOperator* oper, std::shared_ptr<EulNode> right) {
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

EulExpressionType EulInfixExp::getExpressionType() { return EulExpressionType::INFIX_EXP; }
//endregion



//region SUFFIX EXPRESSION
EulSuffixExp::EulSuffixExp(std::shared_ptr<EulNode> exp, EulOperator* oper) {
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

EulExpressionType EulSuffixExp::getExpressionType() { return EulExpressionType::SUFFIX_EXP; }
//endregion



//region TOKEN EXPRESSION
EulTokenExp::EulTokenExp(std::shared_ptr<EulNode> token) { this->token = token; }

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

EulExpressionType EulTokenExp::getExpressionType() { return EulExpressionType::TOKEN; }
//endregion




//region FUNCTION CALL EXPRESSION
EulFunctionCallExp::EulFunctionCallExp(std::shared_ptr<EulNode> func, std::shared_ptr<std::vector<std::shared_ptr<EulNode>>> params) {
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

EulExpressionType EulFunctionCallExp::getExpressionType() { return EulExpressionType::FUNCTION_CALL; }
//endregion




//region FUNCTION CALL EXPRESSION
EulArrayAccessExp::EulArrayAccessExp(std::shared_ptr<EulNode> obj, std::shared_ptr<EulNode> index) {
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

EulExpressionType EulArrayAccessExp::getExpressionType() { return EulExpressionType::ARRAY_ACCESS; }
//endregion



//region EUL EXPRESSION STATEMENT
EulExpStatement::EulExpStatement(std::shared_ptr<EulNode> exp) {
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



//region CODE BLOCK
EulCodeBlock::EulCodeBlock(std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>> statements, std::shared_ptr<EulScope> scope) {
    this->statements = statements;
    this->scope = scope;
}

void EulCodeBlock::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCodeBlock TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulAstType EulCodeBlock::getAstType() { return EulAstType::CODE_BLOCK_TYPE; }


EulExpressionCodeBlock::EulExpressionCodeBlock(std::shared_ptr<EulNode> expression, std::shared_ptr<EulCodeBlock> block) {
    this->block = block;
    this->expression = expression;
}
//endregion


//region FUNCTION
EulFunction::EulFunction(
     std::shared_ptr<EulFunctionType> functionType,
     std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> parameters,
     std::shared_ptr<EulCodeBlock> block) {
    //1. Setup basic fields
    this->functionType = functionType;
    this->parameters = parameters;
    this->block = block;

    //2. Add all parameters to scope
    if (parameters == nullptr) return;      //TODO unit test this TOO
    for (auto& paramDecl : *parameters) {
        auto symbol = std::make_shared<EulSymbol>(
            yy::EulParser::token::VAR, //TODO add const params
            paramDecl->varType
        );
        block->scope->declare(paramDecl->id->name, symbol);
    }
}

void EulFunction::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunction TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulAstType EulFunction::getAstType() { return EulAstType::FUNC_DECLARATION_TYPE; }
//endregion


//region IF STATEMENT
EulIfStatement::EulIfStatement(std::shared_ptr<EulNode> condition, std::shared_ptr<EulCodeBlock> ifBlock) : ifSection(condition, ifBlock) {
    this->elseIfs = nullptr;
    this->elseSection = nullptr;
}

EulIfStatement::EulIfStatement(
    std::shared_ptr<EulNode> condition,
    std::shared_ptr<EulCodeBlock> ifBlock,
    std::shared_ptr<EulCodeBlock> elseSection) :
    ifSection(condition, ifBlock) {
    this->elseIfs = nullptr;
    this->elseSection = elseSection;
}

EulIfStatement::EulIfStatement(
    std::shared_ptr<EulNode> condition,
    std::shared_ptr<EulCodeBlock> ifBlock,
    std::shared_ptr<std::vector<std::shared_ptr<EulExpressionCodeBlock>>> elseIfs,
    std::shared_ptr<EulCodeBlock> elseSection) :
    ifSection(condition, ifBlock) {
    this->elseIfs = elseIfs;
    this->elseSection = elseSection;
}

void EulIfStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulCodeBlock TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulStatementType EulIfStatement::getStatementType() { return EulStatementType::IF_STATEMENT; }
//endregion



//region WHILE STATEMENT
EulWhileStatement::EulWhileStatement(std::shared_ptr<EulNode> condition, std::shared_ptr<EulCodeBlock> ifBlock) : expBlock(condition, ifBlock) {
}

void EulWhileStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulWhileStatement TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulStatementType EulWhileStatement::getStatementType() { return EulStatementType::WHILE_STATEMENT; }
//endregion


//region FUNCTION DECLARATION STATEMENT
EulFuncDeclarationStatement::EulFuncDeclarationStatement(std::shared_ptr<EulFunction> func, std::shared_ptr<EulSymbolNameNode> name) {
    this->func = func;
    this->name = name;
    this->llvmFunc = nullptr;
}

void EulFuncDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFuncDeclarationStatement TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulStatementType EulFuncDeclarationStatement::getStatementType() { return EulStatementType::FUNC_DECLARATION_STATEMENT; }
//endregion
