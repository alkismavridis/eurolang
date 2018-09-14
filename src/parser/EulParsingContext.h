#pragma once

#include <iostream>

/**
    One EulParsingContext will be created every time an eul file parsing begins.
    This EulParsingContext instance will be given in the bison parser as argument, and thus
    will be available during parsing.

    It will contain a reference to the currently parsing EulSourceFile, to the compiler itself,
    and will contain temporary data that the parser needs, such as state flags, scope stack and more.
*/
class EulParsingContext {
    //region FIELDS
    public: Compiler *compiler;
    public: EulSourceFile* sourceFile;
    public: std::shared_ptr<EulScope> currentScope;

    //more to come...
    //endregion



    //region LIFE CYCLE
    public: EulParsingContext(Compiler *compiler, EulSourceFile* sourceFile) {
        this->compiler = compiler;
        this->sourceFile = sourceFile;

        if (sourceFile != nullptr) this->currentScope = sourceFile->scope;
    }
    //endregion


    //region SCOPE MANAGEMENT
    /** Creates a new scope (with this->currentScope as its parent), makes this new scope the current, and returns it. */
    public: std::shared_ptr<EulScope> pushScope() {
        this->currentScope = std::make_shared<EulScope>(this->currentScope);
        return this->currentScope;
    }

    /** Assigns to the current scope the parent of the current scope. */
    public: void popScope() {
        this->currentScope = this->currentScope->superScope;

        //check that we did not exceed the bounds of the top level scope.
        if (this->currentScope == nullptr)
            throw new EulError(EulErrorType::INTERNAL_COMPILER_ERROR, "popScope found null.");
    }
    //endregion

};