#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



class Assert {

    //region NUMERIC
    public: static void equals(long int expected, long int actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
        exit(1);
    }

    public: static void equalsUnsigned(unsigned long int expected, unsigned long int actual, const std::string& label) {
            if (expected==actual) return;
            std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << ".\n\n";
            exit(1);
        }

    public: static void equals(double expected, double actual, double tolerance, const std::string& label) {
        if (abs(expected-actual)<tolerance) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
        exit(1);
    }
    //endregion




    //region TEXT RELATED
    public: static void equals(const std::string& expected, const std::string& actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
    	exit(1);
    }

    public: static void charEquals(char expected, char actual, const std::string& label) {
        if (expected==actual) return;
        std::cout << "\n\n" << label << "\n\tExpected: "<< expected <<",\n\tFound: " << actual << "\n\n";
    	exit(1);
    }
    //endregion




    //region BOOLEANS
    public: static void that(char cond, const std::string& label) {
    	if (cond) return;
    	std::cout << "\n\n"<< label << "\n\tAssert true failed.\n\n";
    	exit(1);
    }

    public: static void thatNot(char cond, const std::string& label) {
    	if (!cond) return;
    	std::cout << "\n\n"<< label << "\n\tAssert false failed.\n\n";
    	exit(1);
    }
    //endregion




    //region POINTERS
    public: static void equals(void* expected, void* actual, const std::string& label) {
    	if (expected==actual) return;
    	std::cout << "\n\n"<< label << "\n\tAssert equals pointers failed.\n\n";
    	exit(1);
    }

    public: static void null(void* ptr, const std::string& label) {
    	if (ptr==0) return;
    	std::cout << "\n\n"<< label << "\n\tAssert null failed.\n\n";
    	exit(1);
    }

    public: static void notNull(void* ptr, const std::string& label) {
    	if (ptr!=0) return;
    	std::cout << "\n\n"<< label << "\n\tAssert not null failed.\n\n";
    	exit(1);
    }
    //endregion




    //region TOKEN TYPES + VALUES
    public: static EulIntToken* intToken(EulToken* token, unsigned long int value, unsigned char size, char isUnsigned, const std::string& label) {
        Assert::equals(EulTokenType::INT, token->getType(), label + "__tokenType");

        EulIntToken* intTok = (EulIntToken*)token;
        Assert::equals(value, intTok->value, label + "__value");
        Assert::equals(size, intTok->size, label + "__size");
        Assert::equals(isUnsigned, intTok->isUnsigned, label + "__isUnsigned");

        return intTok;
    }


    public: static EulFloatToken* floatToken(EulToken* token, double value, unsigned char size, const std::string& label) {
        Assert::equals(EulTokenType::FLOAT, token->getType(), label + "__tokenType");

        EulFloatToken* floatTok = (EulFloatToken*)token;
        Assert::equals(value, floatTok->value, label + "__value");
        Assert::equals(size, floatTok->size, label + "__size");

        return floatTok;
    }

    public: static EulIdToken* idToken(EulToken* token, const std::string& name, const std::string& label) {
        Assert::equals(EulTokenType::ID, token->getType(), label + "__tokenType");

        EulIdToken* idTok = (EulIdToken*)token;
        Assert::equals(name, idTok->name, label + "__name");

        return idTok;
    }

    public: static EulCharToken* charToken(EulToken* token, unsigned long long int value, unsigned char size, const std::string& label) {
        Assert::equals(EulTokenType::CHAR, token->getType(), label + "__tokenType");

        EulCharToken* charTok = (EulCharToken*)token;
        Assert::equals(value, charTok->value, label + "__value");
        Assert::equals(size, charTok->size, label + "__size");

        return charTok;
    }

    public: static EulStringToken* stringToken(EulToken* token, const std::string value, const std::string& label) {
        Assert::equals(EulTokenType::STRING, token->getType(), label + "__tokenType");

        EulStringToken* strTok = (EulStringToken*)token;
        Assert::equals(value, strTok->value, label + "__value");

        return strTok;
    }

    public: static EulType* eulType(EulToken* token, const std::string& name, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EUL_TYPE, ast->getAstType(), label + "__astType");
        EulType* type = (EulType*)ast;

        Assert::equals(name, type->name, label + "__typeName");
        return type;
    }
    //endregion



    //region TOKEN TYPES
    public: static EulAst* ast(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ret = (EulAst*)token;
        return ret;
    }

    public: static EulExpression* expression(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        return (EulExpression*)ast;
    }

    public: static EulInfixExp* infixExp(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        EulExpression* exp = (EulExpression*)ast;

        Assert::equals(EulExpressionType::INFIX_EXP, exp->getExpressionType(), label + "__expressionType");
        return (EulInfixExp*)exp;
    }

    public: static EulPrefixExp* prefixExp(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        EulExpression* exp = (EulExpression*)ast;

        Assert::equals(EulExpressionType::PREFIX_EXP, exp->getExpressionType(), label + "__expressionType");
        return (EulPrefixExp*)exp;
    }

    public: static EulSuffixExp* suffixExp(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        EulExpression* exp = (EulExpression*)ast;

        Assert::equals(EulExpressionType::SUFFIX_EXP, exp->getExpressionType(), label + "__expressionType");
        return (EulSuffixExp*)exp;
    }

    public: static EulFunctionCallExp* funcCall(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        EulExpression* exp = (EulExpression*)ast;

        Assert::equals(EulExpressionType::FUNCTION_CALL, exp->getExpressionType(), label + "__expressionType");
        return (EulFunctionCallExp*)exp;
    }

    public: static EulArrayAccessExp* arrayAccess(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EXPRESSION, ast->getAstType(), label + "__astType");
        EulExpression* exp = (EulExpression*)ast;

        Assert::equals(EulExpressionType::ARRAY_ACCESS, exp->getExpressionType(), label + "__expressionType");
        return (EulArrayAccessExp*)exp;
    }


    public: static EulStatement* statement(EulToken* token, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::STATEMENT, ast->getAstType(), label + "__astType");
        return (EulStatement*)ast;
    }
    //endregion
};









