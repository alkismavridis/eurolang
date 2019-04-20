#pragma once

/*std::shared_ptr<EulType> EulParsingUtils::createEulType(EulParsingContext* ctx, const std::string& typeName) {
    //1. Search the symbol
    auto symbol = ctx->currentScope->get(typeName);
    if (symbol==nullptr || !EulType::isEulType(symbol->value)) return nullptr;
    return ( EulType* ^^^ )symbol->value;
}*/
