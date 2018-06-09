#pragma once

/**
    This is the base class of all tokens. It only provides a getType() method, which will determine if this token
    is an Operator token, an Integer token and so on.
*/
class EulAst : public EulToken {
    public: virtual EulAstType getAstType();
    public: virtual EulTokenType getType() { return AST; }
};