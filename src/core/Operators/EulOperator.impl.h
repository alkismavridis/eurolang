#pragma once


//region BASE CLASS
llvm::Value* EulOperator::performPrefix(llvm::Value* arg, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performPrefix was called, but should not.");
}

llvm::Value* EulOperator::performInfix(llvm::Value* left, llvm::Value* right, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performInfix was called, but should not.");
}

llvm::Value* EulOperator::performSuffix(llvm::Value* arg, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performSuffix was called, but should not.");
}

int EulOperator::getOperatorType() {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getOperatorType was called, but should not.");
}

const std::string EulOperator::getOperatorText() {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getOperatorText was called, but should not.");
}
//endregion




//region AssignOperator
int AssignOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN;
}

const std::string AssignOperator::getOperatorText() {
    return "=";
}
//endregion



//region AssignModOperator
int AssignModOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MOD;
}

const std::string AssignModOperator::getOperatorText() {
    return "=%";
}
//endregion



//region AssignXorOperator
int AssignXorOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_XOR;
}

const std::string AssignXorOperator::getOperatorText() {
    return "=^";
}
//endregion



//region AssignAndOperator
int AssignAndOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_AND;
}

const std::string AssignAndOperator::getOperatorText() {
    return "=&";
}
//endregion




//region AssignStarOperator
int AssignStarOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_STAR;
}

const std::string AssignStarOperator::getOperatorText() {
    return "=*";
}
//endregion


//region AssignMinusOperator
int AssignMinusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_MINUS;
}

const std::string AssignMinusOperator::getOperatorText() {
    return "=-";
}
//endregion


//region AssignPlusOperator
int AssignPlusOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_PLUS;
}

const std::string AssignPlusOperator::getOperatorText() {
    return "=+";
}
//endregion


//region AssignOrOperator
int AssignOrOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_OR;
}

const std::string AssignOrOperator::getOperatorText() {
    return "=|";
}
//endregion


//region AssignDivOperator
int AssignDivOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_DIV;
}

const std::string AssignDivOperator::getOperatorText() {
    return "=/";
}
//endregion


//region AssignLeftShiftOperator
int AssignLeftShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_LSHIFT;
}

const std::string AssignLeftShiftOperator::getOperatorText() {
    return "=<<";
}
//endregion


//region AssignLeftShiftOperator
int AssignRightShiftOperator::getOperatorType() {
    return yy::EulParser::token::ASSIGN_RSHIFT;
}

const std::string AssignRightShiftOperator::getOperatorText() {
    return "=>>";
}
//endregion







//region OrOperator
int OrOperator::getOperatorType() {
    return yy::EulParser::token::OR;
}

const std::string OrOperator::getOperatorText() {
    return "||";
}
//endregion

//region AndOperator
int AndOperator::getOperatorType() {
    return yy::EulParser::token::AND;
}

const std::string AndOperator::getOperatorText() {
    return "&&";
}
//endregion


//region XorOperator
int XorOperator::getOperatorType() {
    return yy::EulParser::token::XOR;
}

const std::string XorOperator::getOperatorText() {
    return "^";
}
//endregion


//region NotEqualsOperator
int NotEqualsOperator::getOperatorType() {
    return yy::EulParser::token::NOT_EQUALS;
}

const std::string NotEqualsOperator::getOperatorText() {
    return "!=";
}
//endregion

//region NotSameOperator
int NotSameOperator::getOperatorType() {
    return yy::EulParser::token::NOT_SAME;
}

const std::string NotSameOperator::getOperatorText() {
    return "!==";
}
//endregion



//region EqualsOperator
int EqualsOperator::getOperatorType() {
    return yy::EulParser::token::EQUALS;
}

const std::string EqualsOperator::getOperatorText() {
    return "==";
}
//endregion

//region SameOperator
int SameOperator::getOperatorType() {
    return yy::EulParser::token::SAME;
}

const std::string SameOperator::getOperatorText() {
    return "===";
}
//endregion



//region LessOperator
int LessOperator::getOperatorType() {
    return yy::EulParser::token::LESS;
}

const std::string LessOperator::getOperatorText() {
    return "<";
}
//endregion


//region LessEqualsOperator
int LessEqualsOperator::getOperatorType() {
    return yy::EulParser::token::LESS_EQUALS;
}

const std::string LessEqualsOperator::getOperatorText() {
    return "<=";
}
//endregion


//region MoreOperator
int MoreOperator::getOperatorType() {
    return yy::EulParser::token::MORE;
}

const std::string MoreOperator::getOperatorText() {
    return ">";
}
//endregion

//region MoreEqualsOperator
int MoreEqualsOperator::getOperatorType() {
    return yy::EulParser::token::MORE_EQUALS;
}

const std::string MoreEqualsOperator::getOperatorText() {
    return ">=";
}
//endregion


//region NotOperator
int NotOperator::getOperatorType() {
    return yy::EulParser::token::NOT;
}

const std::string NotOperator::getOperatorText() {
    return "!";
}
//endregion




//region BinOrOperator
int BinOrOperator::getOperatorType() {
    return yy::EulParser::token::BIN_OR;
}

const std::string BinOrOperator::getOperatorText() {
    return "|";
}
//endregion


//region BinAndOperator
int BinAndOperator::getOperatorType() {
    return yy::EulParser::token::BIN_AND;
}

const std::string BinAndOperator::getOperatorText() {
    return "&";
}
//endregion


//region LeftShiftOperator
int LeftShiftOperator::getOperatorType() {
    return yy::EulParser::token::LSHIFT;
}

const std::string LeftShiftOperator::getOperatorText() {
    return "<<";
}
//endregion


//region RightShiftOperator
int RightShiftOperator::getOperatorType() {
    return yy::EulParser::token::RSHIFT;
}

const std::string RightShiftOperator::getOperatorText() {
    return ">>";
}
//endregion

//region PlusOperator
int PlusOperator::getOperatorType() {
    return yy::EulParser::token::PLUS;
}

const std::string PlusOperator::getOperatorText() {
    return "+";
}

llvm::Value* PlusOperator::performInfix(llvm::Value* left, llvm::Value* right, EulCodeGenContext* ctx) {
    return ctx->builder.CreateBinOp(llvm::Instruction::Add, left, right, "addtmp");
}
//endregion

//region MinusOperator
int MinusOperator::getOperatorType() {
    return yy::EulParser::token::MINUS;
}

const std::string MinusOperator::getOperatorText() {
    return "-";
}

llvm::Value* MinusOperator::performInfix(llvm::Value* left, llvm::Value* right, EulCodeGenContext* ctx) {
    return ctx->builder.CreateBinOp(llvm::Instruction::Sub, left, right, "subtmp");
}
//endregion


//region PercentOperator
int PercentOperator::getOperatorType() {
    return yy::EulParser::token::PERCENT;
}

const std::string PercentOperator::getOperatorText() {
    return "%";
}
//endregion

//region StarOperator
int StarOperator::getOperatorType() {
    return yy::EulParser::token::STAR;
}

const std::string StarOperator::getOperatorText() {
    return "*";
}
//endregion

//region SlashOperator
int SlashOperator::getOperatorType() {
    return yy::EulParser::token::SLASH;
}

const std::string SlashOperator::getOperatorText() {
    return "/";
}
//endregion


//region TildeOperator
int TildeOperator::getOperatorType() {
    return yy::EulParser::token::TILDE;
}

const std::string TildeOperator::getOperatorText() {
    return "~";
}
//endregion


//region DecreaseOperator
int DecreaseOperator::getOperatorType() {
    return yy::EulParser::token::DECREASE;
}

const std::string DecreaseOperator::getOperatorText() {
    return "--";
}
//endregion


//region IncreaseOperator
int IncreaseOperator::getOperatorType() {
    return yy::EulParser::token::INCREASE;
}

const std::string IncreaseOperator::getOperatorText() {
    return "++";
}
//endregion


//region DotOperator
int DotOperator::getOperatorType() {
    return yy::EulParser::token::DOT;
}

const std::string DotOperator::getOperatorText() {
    return ".";
}
//endregion


//region QuestionOperator
int QuestionOperator::getOperatorType() {
    return yy::EulParser::token::QUESTION;
}

const std::string QuestionOperator::getOperatorText() {
    return "?";
}
//endregion


//region ColonOperator
int ColonOperator::getOperatorType() {
    return yy::EulParser::token::COLON;
}

const std::string ColonOperator::getOperatorText() {
    return ":";
}
//endregion


/** Define the global context that includes all operators */
EulOperators EUL_OPERATORS;