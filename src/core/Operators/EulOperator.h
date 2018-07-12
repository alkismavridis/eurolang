#pragma once

class EulOperator : public EulAst {
    public: EulAstType getAstType();
    public: virtual std::string getOperatorText();
    public: virtual int getOperatorType();
};






class AssignOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignModOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignXorOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignAndOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignStarOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignMinusOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};



class AssignPlusOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignOrOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignDivOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignLeftShiftOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AssignRightShiftOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};



class QuestionOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class ColonOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class OrOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class AndOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class BinOrOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class XorOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class BinAndOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class NotEqualsOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class NotSameOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class EqualsOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class SameOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};



class LessOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class LessEqualsOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class MoreOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class MoreEqualsOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};



class LeftShiftOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class RightShiftOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};


class PlusOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class MinusOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class PercentOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class StarOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class SlashOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};


class TildeOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class NotOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class DecreaseOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class IncreaseOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};

class DotOperator : public EulOperator {
    public: std::string getOperatorText();
    public: int getOperatorType();
};