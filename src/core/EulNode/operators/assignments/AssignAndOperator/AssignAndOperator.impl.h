#pragma once


int AssignAndOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_AND;
}

const std::string AssignAndOperator::getOperatorText() {
    return "=&";
}

bool AssignAndOperator::isAssignment() { return true; }
