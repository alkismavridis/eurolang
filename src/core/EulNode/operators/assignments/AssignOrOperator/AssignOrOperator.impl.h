#pragma once

int AssignOrOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_OR;
}

const std::string AssignOrOperator::getOperatorText() {
    return "=|";
}

bool AssignOrOperator::isAssignment() { return true; }
