#pragma once

int DecreaseOperator::getOperatorType() {
    return yy::EulParser::token::DECREASE;
}

const std::string DecreaseOperator::getOperatorText() {
    return "--";
}

bool DecreaseOperator::isAssignment() { return true; }
