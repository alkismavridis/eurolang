#pragma once

int AssignStarOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_STAR;
}

const std::string AssignStarOperator::getOperatorText() {
    return "=*";
}

bool AssignStarOperator::isAssignment() { return true; }
