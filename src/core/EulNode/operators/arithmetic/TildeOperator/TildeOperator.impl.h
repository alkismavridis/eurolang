#pragma once


int TildeOperator::getOperatorType() {
    return yy::EulParser::token::TILDE;
}

const std::string TildeOperator::getOperatorText() {
    return "~";
}

bool TildeOperator::isAssignment() { return false; }
