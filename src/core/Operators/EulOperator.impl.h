#pragma once



//region STATIC UTILS
std::shared_ptr<EulType> EulOperator::doCommonIntMerging(std::shared_ptr<EulType> left, std::shared_ptr<EulType> right, EulCodeGenContext* ctx) {
    //1. Check that operands are indeed integer types
    if (left->getTypeEnum()!=EulTypeEnum::INT_TYPE || right->getTypeEnum()!=EulTypeEnum::INT_TYPE)
        throw EulError(EulErrorType::SEMANTIC, "Int type expected.");

    //2. Cast them into integers
    const auto leftAsInt = static_cast<EulIntegerType*>(left.get());
    const auto rightAsInt = static_cast<EulIntegerType*>(right.get());

    //3. Decide the resulting size, and whether the result is unsigned or not.
    // The biggest one wins for size, and unsigned wins over signed.
    unsigned char resultSize = (leftAsInt->size > rightAsInt->size) ?
        leftAsInt->size :
        rightAsInt->size;
    bool isResultUnsigned = leftAsInt->isUnsigned || rightAsInt->isUnsigned;

    //4. Find the result type, according to the above constrains, and return in
    switch(resultSize) {
        case 8:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint8Type :
                ctx->compiler->program.nativeTypes.int8Type;

        case 16:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint16Type :
                ctx->compiler->program.nativeTypes.int16Type;

        case 32:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint32Type :
                ctx->compiler->program.nativeTypes.int32Type;

        case 64:
            return isResultUnsigned?
                ctx->compiler->program.nativeTypes.uint64Type :
                ctx->compiler->program.nativeTypes.int64Type;

        default: throw EulError(EulErrorType::SEMANTIC, "Wrong int size: " + std::to_string(resultSize));
    }
}
//endregion




//region BASE CLASS
llvm::Value* EulOperator::performPrefix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performPrefix was called, but should not.");
}
std::shared_ptr<EulType> EulOperator::getPrefixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getPrefixResultType was called, but should not.");
}


llvm::Value* EulOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performInfix was called, but should not.");
}
std::shared_ptr<EulType> EulOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getInfixResultType was called, but should not.");
}


llvm::Value* EulOperator::performSuffix(llvm::Value* arg, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::performSuffix was called, but should not.");
}
std::shared_ptr<EulType> EulOperator::getSuffixResultType(std::shared_ptr<EulType> inputType, EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulOperator::getSuffixResultType was called, but should not.");
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

llvm::Value* LeftShiftOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulIntegerType> targetType, EulCodeGenContext* ctx) {
    //we know that this is an int, because getInfixResultType() returns always an int type
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetType->getLlvmType(ctx));

    if (targetLlvmType != left->getType()) left = ctx->castToInteger(left, targetLlvmType, targetType.get());
    if (targetLlvmType != right->getType()) right = ctx->castToInteger(right, targetLlvmType, targetType.get());

    return ctx->builder.CreateBinOp(llvm::Instruction::Shl, left, right);
}

std::shared_ptr<EulType> LeftShiftOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    return EulOperator::doCommonIntMerging(leftType, rightType, ctx);
}
//endregion


//region RightShiftOperator
int RightShiftOperator::getOperatorType() {
    return yy::EulParser::token::RSHIFT;
}

const std::string RightShiftOperator::getOperatorText() {
    return ">>";
}

llvm::Value* RightShiftOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulIntegerType> targetType, EulCodeGenContext* ctx) {
    //we know that this is an int, because getInfixResultType() returns always an int type
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetType->getLlvmType(ctx));

    if (targetLlvmType != left->getType()) left = ctx->castToInteger(left, targetLlvmType, targetType.get());
    if (targetLlvmType != right->getType()) right = ctx->castToInteger(right, targetLlvmType, targetType.get());

    return ctx->builder.CreateBinOp(llvm::Instruction::Shl, left, right);
}
std::shared_ptr<EulType> RightShiftOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    return EulOperator::doCommonIntMerging(leftType, rightType, ctx);
}
//endregion

//region PlusOperator
int PlusOperator::getOperatorType() {
    return yy::EulParser::token::PLUS;
}

const std::string PlusOperator::getOperatorText() {
    return "+";
}

llvm::Value* PlusOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    //TODO we are not sure that this is an IntegerType... This must be examined.
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetType->getLlvmType(ctx));
    auto targetEulType = static_cast<EulIntegerType*>(targetType.get());

    if (targetLlvmType != left->getType()) left = ctx->castToInteger(left, targetLlvmType, targetEulType);
    if (targetLlvmType != right->getType()) right = ctx->castToInteger(right, targetLlvmType, targetEulType);

    return ctx->builder.CreateBinOp(llvm::Instruction::Add, left, right);
}
std::shared_ptr<EulType> PlusOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    return EulOperator::doCommonIntMerging(leftType, rightType, ctx);
}
//endregion

//region MinusOperator
int MinusOperator::getOperatorType() {
    return yy::EulParser::token::MINUS;
}

const std::string MinusOperator::getOperatorText() {
    return "-";
}

llvm::Value* MinusOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    //TODO we are not sure that this is an IntegerType... This must be examined.
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetType->getLlvmType(ctx));
    auto targetEulType = static_cast<EulIntegerType*>(targetType.get());

    if (targetLlvmType != left->getType()) left = ctx->castToInteger(left, targetLlvmType, targetEulType);
    if (targetLlvmType != right->getType()) right = ctx->castToInteger(right, targetLlvmType, targetEulType);

    return ctx->builder.CreateBinOp(llvm::Instruction::Sub, left, right);
}
std::shared_ptr<EulType> MinusOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    return EulOperator::doCommonIntMerging(leftType, rightType, ctx);
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

llvm::Value* StarOperator::performInfix(llvm::Value* left, llvm::Value* right, std::shared_ptr<EulType> targetType, EulCodeGenContext* ctx) {
    //TODO we are not sure that this is an IntegerType... This must be examined.
    auto targetLlvmType = static_cast<llvm::IntegerType*>(targetType->getLlvmType(ctx));
    auto targetEulType = static_cast<EulIntegerType*>(targetType.get());

    if (targetLlvmType != left->getType()) left = ctx->castToInteger(left, targetLlvmType, targetEulType);
    if (targetLlvmType != right->getType()) right = ctx->castToInteger(right, targetLlvmType, targetEulType);

    return ctx->builder.CreateBinOp(llvm::Instruction::Mul, left, right);
}
std::shared_ptr<EulType> StarOperator::getInfixResultType(std::shared_ptr<EulType> leftType, std::shared_ptr<EulType> rightType, EulCodeGenContext* ctx) {
    return EulOperator::doCommonIntMerging(leftType, rightType, ctx);
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