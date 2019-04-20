#pragma once

int AssignRightShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_RSHIFT;
}

const std::string AssignRightShiftOperator::getOperatorText() {
    return "=>>";
}

bool AssignRightShiftOperator::isAssignment() { return true; }
