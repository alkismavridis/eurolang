#pragma once

int IncreaseOperator::getOperatorType() {
    return yy::EulParser::token::INCREASE;
}

const std::string IncreaseOperator::getOperatorText() {
    return "++";
}

bool IncreaseOperator::isAssignment() { return true; }
