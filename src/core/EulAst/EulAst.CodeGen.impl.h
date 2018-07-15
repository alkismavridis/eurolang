#pragma once



//region STATEMENTS
void VarDeclarationStatement::generateCode(EulCodeGenerator* gen) {
    std::cout << "VarDeclarationStatement" << std::endl;
    //return nullptr; //TODO
}

void EulExpStatement::generateCode(EulCodeGenerator* gen) {
    std::cout << "EulExpStatement" << std::endl;
    //return nullptr; //TODO
}
//endregion




//region EXPRESSIONS
llvm::Value* EulArrayAccessExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulArrayAccessExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulFunctionCallExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulFunctionCallExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulInfixExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulInfixExp" << std::endl;

    //1. Calculate the two operands
    llvm::Value* leftValue = this->left->generateValue(gen);
    llvm::Value* rightValue = this->right->generateValue(gen);
    if (!leftValue || !rightValue) return nullptr;

    //2. Return the operation
    //TODO performence. Replace operator type with an actual object that will wxecute this function, avoiding this switch statement:
    switch(this->operatorType) {
        case yy::EulParser::token::PLUS:
            return gen->builder.CreateFAdd(leftValue, rightValue, "addtmp");

        case yy::EulParser::token::MINUS:
            return gen->builder.CreateFSub(leftValue, rightValue, "subtmp");

        case yy::EulParser::token::ASSIGN:
            return gen->builder.CreateFSub(leftValue, rightValue, "subtmp");

        default:
            throw EulError(EulErrorType::SEMANTIC, "Unknown infix operator: " + std::to_string(this->operatorType));
    }
}

llvm::Value* EulPrefixExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulPrefixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulSuffixExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulSuffixExp" << std::endl;
    return nullptr; //TODO
}

llvm::Value* EulTokenExp::generateValue(EulCodeGenerator* gen) {
    std::cout << "EulTokenExp" << std::endl;
    return nullptr; //TODO what this even means?
}
//endregion