#pragma once

class AssignXorOperator : public EulOperator {
    public: int getOperatorType();
    public: const std::string getOperatorText();
    public: bool isAssignment();
};
