#pragma once



/**
    A scope defines the life cycle and the access of the variables that are declared inside it.
    Every scope has a parent scope.

    The top-level scope of each source file has as its parent the EulGlobalScope, that belongs to the whole program.
    The EulGlobalScope contains definitions that are globally available to every part of every eul file.
    This will contain stuff like basic types definitions (Int, Float, etc), build-in functions (like print, exit, etc).

    The EulGlobalScope is special in the sense that is defined from the language itself, and cannot be manipulated by any source file.
    EulGlobalScope is the only scope that has no superScope.
*/
class EulScope {
    //region FIELDS
    public: EulScope* superScope;
    public: std::map<std::string, std::shared_ptr<EulSymbol>> declarations;
    //endregion



    //region LIFE CYCLE
    public: EulScope(EulScope* superScope);
    public: void reset();
    //endregion



    //region DECLARATION MANAGEMENT
    public: std::shared_ptr<EulSymbol> get(const std::string& key);

    public: std::shared_ptr<EulSymbol> getOwnSymbol(const std::string& key);

    public: int getDeclarationCount();

    /**
        Declares the symbol, if it is not already declared on this scope (parent scopes are not included on the search).
        Returns true if the declaration was successful. false if the symbol was already defined in this scope.
    */
    public: bool declare(const std::string& key, std::shared_ptr<EulSymbol> symbol);

    /** Used by the parser to add variables into the scope. */
    public: void declare(VarDeclarationStatement* stmt);   //TODO unit test
    //endregion
};