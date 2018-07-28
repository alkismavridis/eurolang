#pragma once

EulType* EulParsingUtils::createEulType(EulParsingContext* ctx, const std::string& typeName) {
    //1. Search the symbol
    EulSymbol* symbol = ctx->currentScope->get(typeName);

    //2. Check if the token exists, and whether it is a type
    if (symbol!=nullptr && EulType::isEulType(symbol->value)) {
        EulType* type = (EulType*) symbol->value;

        //2.1 Maybe the found type is itself a LateDefinedType...
        if (type->isLateDeclared() && type->llvmType == nullptr) return new LateDefinedType(typeName);

        //2.2 It is a defined type. Return a copy of it.
        return new EulType(type->llvmType);
    }

    //Not found or not a type: return LateDefinedType
    return new LateDefinedType(typeName);
}