#pragma once


class EulParsingUtils {
    //region SYMBOL DECLARATIONS
    /*public: static void addSymbolsToSourceFile(int changeType, std::vector<VarDeclaration*>* newDeclarations, EulParsingContext* ctx) {
        if (newDeclarations == nullptr) return;


        EulScope* scope = &ctx->sourceFile->scope;
        for (auto const& decl : *newDeclarations) {
            const bool success = scope->declare(decl->id->name, new EulSymbol(changeType, decl->varType, decl->value, 0));
            if (!success) ctx->compiler->addError(EulErrorType::SEMANTIC, "Duplicate symbol declaration: "+decl->id->name);
        }
    }*/



    public: static EulType* createEulType(EulParsingContext* ctx, const std::string& typeName);
    //endregion
};