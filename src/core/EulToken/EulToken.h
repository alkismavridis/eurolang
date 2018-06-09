#pragma once

/**
    This is the base class of all tokens. It only provides a getType() method, which will determine if this token
    is an Operator token, an Integer token and so on.
*/
class EulToken {
    public: virtual ~EulToken();
    public: virtual EulTokenType getType();
};

std::ostream& operator<<(std::ostream& os, EulToken* tok);