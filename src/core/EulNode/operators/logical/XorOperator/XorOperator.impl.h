#pragma once

int XorOperator::getOperatorType() {
    return yy::EulParser::token::XOR;
}

const std::string XorOperator::getOperatorText() {
    return "^";
}

bool XorOperator::isAssignment() { return false; }
