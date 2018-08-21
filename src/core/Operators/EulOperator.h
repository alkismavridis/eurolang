#pragma once

class EulOperator {
    public: virtual std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    public: virtual llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    public: virtual std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: virtual llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    public: virtual std::shared_ptr<EulType> getSuffixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    public: virtual llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    public: virtual int getOperatorType();
    public: virtual const std::string getOperatorText();


    //region STATIC UTILS
    public: static std::shared_ptr<EulType> doCommonIntMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx);
    //endregion
};



//ASSIGNMENT OPERATIONS
class AssignOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class AssignModOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignXorOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignAndOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignStarOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignMinusOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignPlusOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignOrOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignDivOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignLeftShiftOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class AssignRightShiftOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};


//LOGICAL OPERATORS
class OrOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class AndOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class XorOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};


class NotEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class NotSameOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class EqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class SameOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class LessOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class LessEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class MoreOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class MoreEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class NotOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};




//ARITHMETIC OPERATIONS
class BinOrOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class BinAndOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);   //VALUE OF POINTER
};

class LeftShiftOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulIntegerType> targetType, EulCodeGenContext* ctx);
};

class RightShiftOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulIntegerType> targetType, EulCodeGenContext* ctx);
};

class PlusOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class MinusOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class PercentOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx); //ADDRESS OF
};

class StarOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class SlashOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};

class TildeOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class DecreaseOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);


    //public: llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class IncreaseOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    //public: std::shared_ptr<EulType> getSuffixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx);
    //public: llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class DotOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();

    //public: std::shared_ptr<EulType> getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx);
    //public: llvm::Value* performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx)
};


//SPOOKY STUFF
class QuestionOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
};

class ColonOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    //public: const std::string getOperatorText();
};



//region GLOBAL OBJECT
class EulOperators {
    public: AssignOperator assignOperator;
    public: AssignModOperator assignModOperator;
    public: AssignXorOperator assignXorOperator;
    public: AssignAndOperator assignAndOperator;
    public: AssignStarOperator assignStarOperator;
    public: AssignMinusOperator assignMinusOperator;
    public: AssignPlusOperator assignPlusOperator;
    public: AssignOrOperator assignOrOperator;
    public: AssignDivOperator assignDivOperator;
    public: AssignLeftShiftOperator assignLeftShiftOperator;
    public: AssignRightShiftOperator assignRightShiftOperator;

    public: OrOperator orOperator;
    public: AndOperator andOperator;
    public: XorOperator xorOperator;
    public: NotEqualsOperator notEqualsOperator;
    public: NotSameOperator notSameOperator;
    public: EqualsOperator equalsOperator;
    public: SameOperator sameOperator;
    public: LessOperator lessOperator;
    public: LessEqualsOperator lessEqualsOperator;
    public: MoreOperator moreOperator;
    public: MoreEqualsOperator moreEqualsOperator;
    public: NotOperator notOperator;

    public: BinOrOperator binOrOperator;
    public: BinAndOperator binAndOperator;
    public: LeftShiftOperator leftShiftOperator;
    public: RightShiftOperator rightShiftOperator;
    public: PlusOperator plusOperator;
    public: MinusOperator minusOperator;
    public: PercentOperator percentOperator;
    public: StarOperator starOperator;
    public: SlashOperator slashOperator;
    public: TildeOperator tildeOperator;
    public: DecreaseOperator decreaseOperator;
    public: IncreaseOperator increaseOperator;
    public: DotOperator dotOperator;

    public: QuestionOperator questionOperator;
    public: ColonOperator colonOperator;
};


extern EulOperators EUL_OPERATORS;
//endregion