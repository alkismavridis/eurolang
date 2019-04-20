#pragma once

int AssignPlusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_PLUS;
}

const std::string AssignPlusOperator::getOperatorText() {
    return "=+";
}

bool AssignPlusOperator::isAssignment() { return true; }
