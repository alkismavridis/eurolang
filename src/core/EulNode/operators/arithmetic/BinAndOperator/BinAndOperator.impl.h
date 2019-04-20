#pragma once


int BinAndOperator::getOperatorType() {
    return yy::EulParser::token::BIN_AND;
}

const std::string BinAndOperator::getOperatorText() {
    return "&";
}

bool BinAndOperator::isAssignment() { return false; }
