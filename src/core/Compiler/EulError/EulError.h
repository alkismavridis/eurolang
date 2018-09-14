#pragma once

enum EulErrorType {
    NO_ERROR,
    LEXER,
    SYNTAX,
    SEMANTIC,
    INTERNAL_COMPILER_ERROR,
    PARAMS_ERROR,
    NOT_IMPLEMENTED
};


class EulError {
    public: int type; //NOTE; one of error type enum
    public: std::string message;

    public: EulError(int type, const std::string& message);
    public: EulError();

    public: void reset();
};