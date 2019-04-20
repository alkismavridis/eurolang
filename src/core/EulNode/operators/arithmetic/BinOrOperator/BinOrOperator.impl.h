#pragma once


int BinOrOperator::getOperatorType() {
    return yy::EulParser::token::BIN_OR;
}

const std::string BinOrOperator::getOperatorText() {
    return "|";
}

bool BinOrOperator::isAssignment() { return false; }
