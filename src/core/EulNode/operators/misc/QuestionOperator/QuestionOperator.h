#pragma once

class QuestionOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};
