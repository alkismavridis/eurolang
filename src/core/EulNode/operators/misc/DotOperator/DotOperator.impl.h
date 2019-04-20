#pragma once

int DotOperator::getOperatorType() {
    return yy::EulParser::token::DOT;
}

const std::string DotOperator::getOperatorText() {
    return ".";
}

bool DotOperator::isAssignment() { return false; }
