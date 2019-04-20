#pragma once

int OrOperator::getOperatorType() {
    return yy::EulParser::token::OR;
}

const std::string OrOperator::getOperatorText() {
    return "||";
}

bool OrOperator::isAssignment() { return false; }
