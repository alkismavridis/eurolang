#pragma once

#include <functional>
#include "model/error/EulLogger.h"
#include "model/ast/file/AstRoot.h"



/**
    Implementations may throw EulException on fatal error.
    It can also call log.error, lor.ward and log.info to communicate messages to the user.

    If log.error() is called more than 0 times, the returned AST will not be parsed
    and the compiling process will end in failure.
*/
using AstProvider = std::function<
    std::unique_ptr<const AstRoot>(
        const std::string& fileName,
        EulLogger* log
    )
>;
