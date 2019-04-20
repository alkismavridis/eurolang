#pragma once

int AssignMinusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MINUS;
}

const std::string AssignMinusOperator::getOperatorText() {
    return "=-";
}

bool AssignMinusOperator::isAssignment() { return true; }
