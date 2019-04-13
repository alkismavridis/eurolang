#pragma once

class EulOperator {
    public: virtual llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);


    public: virtual llvm::Value* performInfix(
        llvm::Value* left,  //the left value
        std::shared_ptr<EulType> leftType,  //the compile time type of the left value
        llvm::Value* right,                 //the right value
        std::shared_ptr<EulType> rightType, //the compile time type of the right value
        std::shared_ptr<EulType>* resultTypeAddress,    //we must store the result compile-time type here
        EulCodeGenContext* ctx
    );

    /** same as performInfix, but it accepts a symbol instead of a value as left operand, in order to perform assignments. */
    public: virtual llvm::Value* assignInfix(
        EulSymbol* sym,                     //the symbol to assign to
        llvm::Value* right,                 //the right value
        std::shared_ptr<EulType> rightType, //the compile time type of the right value
        std::shared_ptr<EulType>* resultTypeAddress,    //we must store the result compile-time type here
        EulCodeGenContext* ctx
    );


    public: virtual llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);

    public: virtual int getOperatorType();
    public: virtual const std::string getOperatorText();
    public: virtual bool isAssignment();
};



//ASSIGNMENT OPERATIONS
#include "AssignOperator/AssignOperator.h"

class AssignModOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignXorOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignAndOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignStarOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignMinusOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignPlusOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignOrOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignDivOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignLeftShiftOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class AssignRightShiftOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};


//LOGICAL OPERATORS
class OrOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class AndOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class XorOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};


class NotEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class NotSameOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class EqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class SameOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class LessOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class LessEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class MoreOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class MoreEqualsOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();
    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class NotOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};




//ARITHMETIC OPERATIONS
class BinOrOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class BinAndOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);   //ADDRESS OF
};

class LeftShiftOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class RightShiftOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class PlusOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class MinusOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class PercentOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx); //ADDRESS OF
};

class StarOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class SlashOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};

class TildeOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class DecreaseOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
    //public: llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class IncreaseOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
    //public: llvm::Value* performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx);
};

class DotOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();

    //public: llvm::Value* performInfix(llvm::Value* left, std::shared_ptr<EulType> leftType, llvm::Value* right, std::shared_ptr<EulType> rightType, std::shared_ptr<EulType>* resultTypeAddr, EulCodeGenContext* ctx);
};


//SPOOKY STUFF
class QuestionOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};

class ColonOperator : public EulOperator {
    public: const std::string getOperatorText();
    public: int getOperatorType();
    public: bool isAssignment();
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
