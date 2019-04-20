#pragma once

int AndOperator::getOperatorType() {
    return yy::EulParser::token::AND;
}

const std::string AndOperator::getOperatorText() {
    return "&&";
}

bool AndOperator::isAssignment() { return false; }
