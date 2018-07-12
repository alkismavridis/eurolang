#pragma once

enum EulErrorType {
    NO_ERROR,
    LEXER,
    SYNTAX,
    SEMANTIC,
    PARAMS_ERROR
};


class EulError {
    public: int type; //NOTE; one of error type enum
    public: std::string message;

    public: EulError(int type, const std::string& message);
    public: EulError();

    public: void reset();
};