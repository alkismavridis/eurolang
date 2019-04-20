#pragma once

int ColonOperator::getOperatorType() {
    return yy::EulParser::token::COLON;
}

const std::string ColonOperator::getOperatorText() {
    return ":";
}

bool ColonOperator::isAssignment() { return false; }
