#pragma once





    # include <iostream>


class EulParserUtils {
    //region SYMBOL DECLARATIONS
    public: static void addSymbolsToSourceFile(int changeType, std::vector<VarDeclaration*>* newDeclarations, EulParsingContext* ctx) {
        if (newDeclarations == nullptr) return;


        std::map<std::string, EulSymbol*>* alreadyDeclaredSymbols = &ctx->sourceFile->symbols;
        for (auto const& decl : *newDeclarations) {
            const std::string name = decl->id->name;

            //1. Check if symbol is already declared in the scope
            if(ctx->sourceFile->getSymbol(name) != nullptr) {
                ctx->compiler->addError(EulErrorType::SEMANTIC, "Illegal attempt to redefine symbol: " + name);
                return;
            }

            alreadyDeclaredSymbols->operator[](name) = new EulSymbol(changeType, name, decl->varType, decl->value);
        }
    }
    //endregion
};