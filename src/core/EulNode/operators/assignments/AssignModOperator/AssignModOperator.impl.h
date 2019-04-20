#pragma once

int AssignModOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MOD;
}

const std::string AssignModOperator::getOperatorText() {
    return "=%";
}

bool AssignModOperator::isAssignment() { return true; }
