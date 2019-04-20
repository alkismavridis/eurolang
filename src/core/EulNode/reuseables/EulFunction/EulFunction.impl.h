#pragma once

EulFunction::EulFunction(
     std::shared_ptr<EulFunctionType> functionType,
     std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> parameters,
     std::shared_ptr<EulCodeBlock> block) {
    //1. Setup basic fields
    this->functionType = functionType;
    this->parameters = parameters;
    this->block = block;

    //2. Add all parameters to scope
    if (parameters == nullptr) return;      //TODO unit test this TOO
    for (auto& paramDecl : *parameters) {
        auto symbol = std::make_shared<EulSymbol>(
            yy::EulParser::token::VAR, //TODO add const params
            paramDecl->varType
        );
        block->scope->declare(paramDecl->id->name, symbol);
    }
}

void EulFunction::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunction TODO\"," << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulNodeType EulFunction::getNodeType() { return EulNodeType::FUNC_DECLARATION_TYPE; }
