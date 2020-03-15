#pragma once

#include "model/types/AnyType.h"
#include "model/types/BooleanType.h"
#include "model/types/CharType.h"
#include "model/types/FloatType.h"
#include "model/types/IntType.h"
#include "model/types/VoidType.h"

struct SuperGlobals {
    const AnyType anyType;
    const BooleanType booleanType;
    const CharType char8Type;
    const CharType char16Type;
    const CharType char32Type;
    const FloatType float32Type;
    const FloatType float64Type;
    const IntType int8Type;
    const IntType uInt8Type;
    const IntType int16Type;
    const IntType uInt16Type;
    const IntType int32Type;
    const IntType uInt32Type;
    const IntType int64Type;
    const IntType uInt64Type;
    const VoidType voidType;

    SuperGlobals() :
        char8Type(8),
        char16Type(16),
        char32Type(32),
        float32Type(32),
        float64Type(64),
        int8Type(8, false),
        uInt8Type(8, true),
        int16Type(16, false),
        uInt16Type(16, true),
        int32Type(32, false),
        uInt32Type(32, true),
        int64Type(64, false),
        uInt64Type(64, true) {}
};
