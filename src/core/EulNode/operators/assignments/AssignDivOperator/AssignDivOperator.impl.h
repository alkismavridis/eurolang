#pragma once

int AssignDivOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_DIV;
}

const std::string AssignDivOperator::getOperatorText() {
    return "=/";
}

bool AssignDivOperator::isAssignment() { return true; }
