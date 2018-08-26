#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



class Assert {

    public: static void fail(const std::string& message) {
        std::cout << message << std::endl;
        exit(1);
    }

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

    /*public: static EulType* eulType(EulToken* token, const llvm::Type* llvmType, const std::string& label) {
        Assert::equals(EulTokenType::AST, token->getType(), label + "__tokenType");
        EulAst* ast = (EulAst*)token;

        Assert::equals(EulAstType::EUL_TYPE, ast->getAstType(), label + "__astType");
        EulType* ret = (EulType*)ast;

        Assert::equals((void*)llvmType, (void*)ret->llvmType, label + "__llvmType");
        return ret;
    }*/
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
        EulAst* ast = static_cast<EulAst*>(token);

        Assert::equals(EulAstType::STATEMENT, ast->getAstType(), label + "__astType");
        return static_cast<EulStatement*>(ast);
    }

    public: static ReturnStatement* returnStatement(EulToken* token, const std::string& label) {
        EulStatement* stmt = statement(token, label);
        Assert::equals(EulStatementType::RETURN_STATEMENT, stmt->getStatementType(), label + "__getStatement");
        return static_cast<ReturnStatement*>(stmt);
    }
    //endregion



    //region LLVM TESTS
    public: static llvm::ConstantInt* llvmIntConstant(llvm::Value* testVal, unsigned long int size, unsigned long int expected, const std::string& label) {
        Assert::that(llvm::ConstantInt::classof(testVal), label+"__isInteger");

        auto asInt = static_cast<llvm::ConstantInt*>(testVal);
        Assert::equals(size, asInt->getType()->getBitWidth(), label + "__size");
        Assert::equals(expected, asInt->getValue().getZExtValue(), label + "__value");

        return asInt;
    }

    public: static llvm::ConstantFP* llvmFloatConstant(llvm::Value* testVal, unsigned long int size, double expected, double tolerance, const std::string& label) {
        Assert::that(testVal->getType()->isFloatTy() || testVal->getType()->isDoubleTy(), label+"__isFloat");

        auto asFloat = static_cast<llvm::ConstantFP*>(testVal);
        Assert::equals(size, asFloat->getType()->getPrimitiveSizeInBits(), label + "__size");

        double testPrimitiveValue = testVal->getType()->isFloatTy()?
            asFloat->getValueAPF().convertToFloat() :
            asFloat->getValueAPF().convertToDouble();
        Assert::equals(expected, testPrimitiveValue, tolerance, label + "__value");

        return asFloat;
    }

    public: static llvm::Value* llvmStringConstant(llvm::Value* testVal, const std::string& expected, EulCodeGenContext* ctx, const std::string& label) {
        Assert::that(testVal->getType()->isPointerTy(), label+"__isPointer");
        Assert::equals(testVal->getType()->getArrayElementType(), llvm::IntegerType::get(ctx->context, 8), label+"__type");

        //2. Check the global symbol entry
        auto globalVar = ctx->module->getNamedGlobal (".glob" + std::to_string(ctx->globIndex - 1));
        Assert::notNull(globalVar, label+"__globExistence");
        Assert::that(globalVar->hasInitializer(), label+"__isInitialized");
        Assert::that(globalVar->isConstant(), label+"__isConstant ");
        Assert::equals(llvm::GlobalValue::LinkageTypes::PrivateLinkage, globalVar->getLinkage(), label+"__linkage");
        Assert::that(llvm::GlobalValue::UnnamedAddr::Global == globalVar->getUnnamedAddr(), label+"__unnamedAddr");

        //3. Check the global symbol content
        auto stringValue = globalVar->getInitializer();

        Assert::that(llvm::ConstantDataArray::classof(stringValue), label+"__initClass");
        llvm::ConstantDataArray* asLlvmArray = static_cast<llvm::ConstantDataArray*>(stringValue);
        Assert::that(asLlvmArray->isString(), label+"__isString");
        Assert::equals(expected, asLlvmArray->getAsCString(), label+"__asString");

        return testVal;
    }
    //endregion
};