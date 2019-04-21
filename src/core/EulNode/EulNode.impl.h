#pragma once


#include "leaf_nodes/EulBooleanNode/EulBooleanNode.impl.h"
#include "leaf_nodes/EulCharNode/EulCharNode.impl.h"
#include "leaf_nodes/EulFloatNode/EulFloatNode.impl.h"
#include "leaf_nodes/EulIntNode/EulIntNode.impl.h"
#include "leaf_nodes/EulStringNode/EulStringNode.impl.h"
#include "leaf_nodes/EulSymbolNameNode/EulSymbolNameNode.impl.h"

#include "expressions/EulExpression/EulExpression.impl.h"
#include "expressions/EulArrayAccessExp/EulArrayAccessExp.impl.h"
#include "expressions/EulFunctionCallExp/EulFunctionCallExp.impl.h"
#include "expressions/EulInfixExp/EulInfixExp.impl.h"
#include "expressions/EulPrefixExp/EulPrefixExp.impl.h"
#include "expressions/EulSuffixExp/EulSuffixExp.impl.h"

#include "statements/EulStatement/EulStatement.impl.h"
#include "statements/EulExportStatement/EulExportStatement.impl.h"
#include "statements/EulExpStatement/EulExpStatement.impl.h"
#include "statements/EulFuncDeclarationStatement/EulFuncDeclarationStatement.impl.h"
#include "statements/EulIfStatement/EulIfStatement.impl.h"
#include "statements/EulImportStatement/EulImportStatement.impl.h"
#include "statements/EulWhileStatement/EulWhileStatement.impl.h"
#include "statements/ReturnStatement/ReturnStatement.impl.h"
#include "statements/VarDeclarationStatement/VarDeclarationStatement.impl.h"

#include "reuseables/EulCodeBlock/EulCodeBlock.impl.h"
#include "reuseables/VarDeclaration/VarDeclaration.impl.h"
#include "reuseables/EulExpressionCodeBlock/EulExpressionCodeBlock.impl.h"
#include "reuseables/EulFunction/EulFunction.impl.h"

#include "types/EulType/EulType.impl.h"
#include "types/EulAnyType/EulAnyType.impl.h"
#include "types/EulBooleanType/EulBooleanType.impl.h"
#include "types/EulCharType/EulCharType.impl.h"
#include "types/EulFloatType/EulFloatType.impl.h"
#include "types/EulFunctionType/EulFunctionType.impl.h"
#include "types/EulIntegerType/EulIntegerType.impl.h"
#include "types/EulNamedType/EulNamedType.impl.h"
#include "types/EulPointerType/EulPointerType.impl.h"
#include "types/EulStringType/EulStringType.impl.h"
#include "types/EulVoidType/EulVoidType.impl.h"

#include "operators/EulOperator/EulOperator.impl.h"
#include "operators/assignments/AssignAndOperator/AssignAndOperator.impl.h"
#include "operators/assignments/AssignDivOperator/AssignDivOperator.impl.h"
#include "operators/assignments/AssignLeftShiftOperator/AssignLeftShiftOperator.impl.h"
#include "operators/assignments/AssignMinusOperator/AssignMinusOperator.impl.h"
#include "operators/assignments/AssignModOperator/AssignModOperator.impl.h"
#include "operators/assignments/AssignOperator/AssignOperator.impl.h"
#include "operators/assignments/AssignOrOperator/AssignOrOperator.impl.h"
#include "operators/assignments/AssignPlusOperator/AssignPlusOperator.impl.h"
#include "operators/assignments/AssignRightShiftOperator/AssignRightShiftOperator.impl.h"
#include "operators/assignments/AssignStarOperator/AssignStarOperator.impl.h"
#include "operators/assignments/AssignXorOperator/AssignXorOperator.impl.h"
#include "operators/assignments/IncreaseOperator/IncreaseOperator.impl.h"
#include "operators/assignments/DecreaseOperator/DecreaseOperator.impl.h"

#include "operators/logical/OrOperator/OrOperator.impl.h"
#include "operators/logical/NotOperator/NotOperator.impl.h"
#include "operators/logical/AndOperator/AndOperator.impl.h"
#include "operators/logical/EqualsOperator/EqualsOperator.impl.h"
#include "operators/logical/NotEqualsOperator/NotEqualsOperator.impl.h"
#include "operators/logical/NotSameOperator/NotSameOperator.impl.h"
#include "operators/logical/XorOperator/XorOperator.impl.h"
#include "operators/logical/SameOperator/SameOperator.impl.h"
#include "operators/logical/LessOperator/LessOperator.impl.h"
#include "operators/logical/LessEqualsOperator/LessEqualsOperator.impl.h"
#include "operators/logical/MoreOperator/MoreOperator.impl.h"
#include "operators/logical/MoreEqualsOperator/MoreEqualsOperator.impl.h"

#include "operators/arithmetic/BinAndOperator/BinAndOperator.impl.h"
#include "operators/arithmetic/BinOrOperator/BinOrOperator.impl.h"
#include "operators/arithmetic/LeftShiftOperator/LeftShiftOperator.impl.h"
#include "operators/arithmetic/MinusOperator/MinusOperator.impl.h"
#include "operators/arithmetic/PercentOperator/PercentOperator.impl.h"
#include "operators/arithmetic/PlusOperator/PlusOperator.impl.h"
#include "operators/arithmetic/RightShiftOperator/RightShiftOperator.impl.h"
#include "operators/arithmetic/SlashOperator/SlashOperator.impl.h"
#include "operators/arithmetic/StarOperator/StarOperator.impl.h"
#include "operators/arithmetic/TildeOperator/TildeOperator.impl.h"

#include "operators/misc/DotOperator/DotOperator.impl.h"
#include "operators/misc/ColonOperator/ColonOperator.impl.h"
#include "operators/misc/QuestionOperator/QuestionOperator.impl.h"




//region LIFE CYCLE
EulNode::~EulNode() {}
EulNodeType EulNode::getNodeType() { return EulNodeType::UNKNOWN; }
//endregion



//region SERIALIZATION
void EulNode::toJson(std::ostream& out, int tabs) {
    out << "{\"type\":\"EulNode\"}";
}

std::ostream& operator<<(std::ostream& os, EulNode* tok) {
    tok->toJson(os, 0);
    return os;
}

void EulNode::toJsonArray(std::ostream& out, const std::vector<EulNode*>* tokens, int tabs) {
    out << "[" << std::endl;

    for (auto const& t : *tokens) {
        for (int i=tabs; i>=0; --i) out << "\t";

        if (t!=nullptr) t->toJson(out, tabs+1);
        else out << "null";

        out << "," << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "]";
}

void EulNode::toJsonArray(std::ostream& out, const std::vector<std::shared_ptr<EulNode>> tokens, int tabs) {
    out << "[" << std::endl;

    for (auto const& t : tokens) {
        for (int i=tabs; i>=0; --i) out << "\t";

        if (t!=nullptr) t->toJson(out, tabs+1);
        else out << "null";

        out << "," << std::endl;
    }

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "]";
}
//endregion
