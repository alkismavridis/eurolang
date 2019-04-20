#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>



template <typename Enumeration>
auto enumToInt(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class Assert {

    public: static void fail(const std::string& message) {
        std::cout << message << std::endl;
        exit(1);
    }

    //region NUMERIC
    template <class E>
    static void enumEquals(E expected, E actual, const std::string& label) {
      if (expected==actual) return;
      std::cout << "\n\n" << label << "\n\tExpected: "<<
        enumToInt(expected) <<",\n\tFound: " <<
        enumToInt(actual) << ".\n\n";
      exit(1);
    }

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
    public: static EulIntNode* intToken(EulNode* token, unsigned long int value, unsigned char size, char isUnsigned, const std::string& label) {
      EulIntNode* intTok = dynamic_cast<EulIntNode*>(token);
      Assert::that(intTok!=nullptr, label + "__isEulIntNode");

      Assert::equals(value, intTok->value, label + "__value");
      Assert::equals(size, intTok->size, label + "__size");
      Assert::equals(isUnsigned, intTok->isUnsigned, label + "__isUnsigned");

      return intTok;
    }


    public: static EulFloatNode* floatToken(EulNode* token, double value, unsigned char size, const std::string& label) {
      EulFloatNode* floatTok = dynamic_cast<EulFloatNode*>(token);
      Assert::that(floatTok!=nullptr, label + "__isEulFloatNode");
      Assert::equals(value, floatTok->value, label + "__value");
      Assert::equals(size, floatTok->size, label + "__size");

      return floatTok;
    }

    public: static EulSymbolNameNode* idToken(EulNode* token, const std::string& name, const std::string& label) {
      EulSymbolNameNode* idTok = dynamic_cast<EulSymbolNameNode*>(token);
      Assert::that(idTok!=nullptr, label + "__isEulSymbolNameNode");
      Assert::equals(name, idTok->name, label + "__name");
      return idTok;
    }

    public: static EulCharNode* charToken(EulNode* token, unsigned long long int value, unsigned char size, const std::string& label) {
      EulCharNode* charTok = dynamic_cast<EulCharNode*>(token);
      Assert::that(charTok!=nullptr, label + "__isEulCharNode");
      Assert::equals(value, charTok->value, label + "__value");
      Assert::equals(size, charTok->size, label + "__size");

      return charTok;
    }

    public: static EulStringNode* stringToken(EulNode* token, const std::string value, const std::string& label) {
      EulStringNode* strTok = dynamic_cast<EulStringNode*>(token);
      Assert::that(strTok!=nullptr, label + "__isEulStringNode");
      Assert::equals(value, strTok->value, label + "__value");

      return strTok;
    }
    //endregion



    //region TOKEN TYPES
    public: static EulExpression* expression(EulNode* token, const std::string& label) {
      EulExpression* ret = dynamic_cast<EulExpression*>(token);
      Assert::that(ret!=nullptr, label + "__isExpression");
      return ret;
    }

    public: static EulInfixExp* infixExp(EulNode* token, const std::string& label) {
      EulInfixExp* ret = dynamic_cast<EulInfixExp*>(token);
      Assert::that(ret!=nullptr, label + "__isInfixExpression");
      return ret;
    }

    public: static EulPrefixExp* prefixExp(EulNode* token, const std::string& label) {
      EulPrefixExp* ret = dynamic_cast<EulPrefixExp*>(token);
      Assert::that(ret!=nullptr, label + "__isEulPrefixExp");
      return ret;
    }

    public: static EulSuffixExp* suffixExp(EulNode* token, const std::string& label) {
      EulSuffixExp* ret = dynamic_cast<EulSuffixExp*>(token);
      Assert::that(ret!=nullptr, label + "__isEulSuffixExp");
      return ret;
    }

    public: static EulFunctionCallExp* funcCall(EulNode* token, const std::string& label) {
      EulFunctionCallExp* ret = dynamic_cast<EulFunctionCallExp*>(token);
      Assert::that(ret!=nullptr, label + "__isEulFunctionCallExp");
      return ret;
    }

    public: static EulArrayAccessExp* arrayAccess(EulNode* token, const std::string& label) {
      EulArrayAccessExp* ret = dynamic_cast<EulArrayAccessExp*>(token);
      Assert::that(ret!=nullptr, label + "__isEulArrayAccessExp");
      return ret;
    }


    public: static EulStatement* statement(EulNode* token, const std::string& label) {
      EulStatement* ret = dynamic_cast<EulStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isEulStatement");
      return ret;
    }

    public: static ReturnStatement* returnStatement(EulNode* token, const std::string& label) {
      ReturnStatement* ret = dynamic_cast<ReturnStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isReturnStatement");
      return ret;
    }

    public: static EulExpStatement* expStatement(EulNode* token, const std::string& label) {
      EulExpStatement* ret = dynamic_cast<EulExpStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isEulExpStatement");
      return ret;
    }

    public: static VarDeclarationStatement* varDeclarationStatement(EulNode* token, const std::string& label) {
      VarDeclarationStatement* ret = dynamic_cast<VarDeclarationStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isVarDeclarationStatement");
      return ret;
    }

    public: static EulIfStatement* ifStatement(EulNode* token, const std::string& label) {
      EulIfStatement* ret = dynamic_cast<EulIfStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isEulIfStatement");
      return ret;
    }

    public: static EulWhileStatement* whileStatement(EulNode* token, const std::string& label) {
      EulWhileStatement* ret = dynamic_cast<EulWhileStatement*>(token);
      Assert::that(ret!=nullptr, label + "__isEulWhileStatement");
      return ret;
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
