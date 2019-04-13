#pragma once

enum class EulErrorType {
    NO_ERROR,
    LEXER,
    SYNTAX,
    SEMANTIC,
    INTERNAL_COMPILER_ERROR,
    PARAMS_ERROR,
    NOT_IMPLEMENTED
};


class EulError {
    public: EulErrorType type; //NOTE; one of error type enum
    public: std::string message;

    public: EulError(EulErrorType type, const std::string& message);
    public: EulError();

    public: void reset();
};
