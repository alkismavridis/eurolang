#pragma once

#include "analyser/model/error/EulLogger.h"
#include "ast/file/AstRoot.h"

struct AstProvider {
    /**
        Implementation may throw EulException on fatal error.
        It can also call log.error, lor.ward and log.info to communicate messages to the user.

        If log.error() is called more than 0 times, the returned AST will not be parsed
        and the compiling process will end in failure.
    */
    virtual std::unique_ptr<const AstRoot> get(const std::string& fileName, EulLogger* log);
};
