#pragma once

int AssignLeftShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_LSHIFT;
}

const std::string AssignLeftShiftOperator::getOperatorText() {
    return "=<<";
}

bool AssignLeftShiftOperator::isAssignment() { return true; }
