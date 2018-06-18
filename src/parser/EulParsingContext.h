#pragma once

/**
    One EulParsingContext will be created every time an eul file parsing begins.
    This EulParsingContext instance will be given in the bison parser as argument, and thus
    will be available during parsing.

    It will contain a reference to the currently parsing EulSourceFile, to the compiler itself,
    and will contain temporary data that the parser needs, such as state flags, scope stack andmore.
*/
class EulParsingContext {
    //region FIELDS
    public: Compiler *compiler;
    public: EulSourceFile* sourceFile;

    //more to come...
    //endregion



    //region LIFE CYCLE
    public: EulParsingContext(Compiler *compiler, EulSourceFile* sourceFile) {
        this->compiler = compiler;
        this->sourceFile = sourceFile;
    }
    //endregion
};