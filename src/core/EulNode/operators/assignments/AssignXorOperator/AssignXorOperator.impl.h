#pragma once

int AssignXorOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_XOR;
}

const std::string AssignXorOperator::getOperatorText() {
    return "=^";
}

bool AssignXorOperator::isAssignment() { return true; }
