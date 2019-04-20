#pragma once

int QuestionOperator::getOperatorType() {
    return yy::EulParser::token::QUESTION;
}

const std::string QuestionOperator::getOperatorText() {
    return "?";
}

bool QuestionOperator::isAssignment() { return false; }
