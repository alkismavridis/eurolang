/** On this file, we will implement all methods from every header file on this "package". */

#pragma once


#include "LeafNodes/EulBooleanNode/EulBooleanNode.impl.h"
#include "LeafNodes/EulCharNode/EulCharNode.impl.h"
#include "LeafNodes/EulFloatNode/EulFloatNode.impl.h"
#include "LeafNodes/EulIntNode/EulIntNode.impl.h"
#include "LeafNodes/EulStringNode/EulStringNode.impl.h"
#include "LeafNodes/EulSymbolNameNode/EulSymbolNameNode.impl.h"





//region LIFE CYCLE
EulNode::~EulNode() {}
EulTokenType EulNode::getType() { return EulTokenType::UNKNOWN; }
//endregion



//region CORE FUNCTIONS
//endregion



//region CODE GENERATION
llvm::Value* EulNode::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    throw EulError(EulErrorType::SEMANTIC, "EulNode::generateValue was called, but should not!");
}

std::shared_ptr<EulType> EulNode::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    throw EulError(EulErrorType::SEMANTIC, "EulNode::getEulType was called, but should not!");
}
//endregion




//region SERIALIZATION
void EulNode::toJson(std::ostream& out, int tabs) {
    out << "{\"type\":\"EulNode\"}";
}

std::ostream& operator<<(std::ostream& os, EulNode* tok) {
    tok->toJson(os, 0);
    return os;
}

void EulNode::toJson(std::ostream& out, std::vector<EulNode*>* tokens, int tabs) {
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

void EulNode::toJson(std::ostream& out, std::vector<std::shared_ptr<EulNode>> tokens, int tabs) {
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
