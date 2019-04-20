#pragma once

class AssignPlusOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};
