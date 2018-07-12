#pragma once

enum EulExpressionType {
    UNKNOWN_EXP,
    PREFIX_EXP,
    SUFFIX_EXP,
    INFIX_EXP,
    TOKEN,
    FUNCTION_CALL,
    ARRAY_ACCESS
};