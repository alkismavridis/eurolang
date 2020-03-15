#pragma once

#include <functional>

#include "model/ast/file/AstRoot.h"
#include "model/error/EulLogger.h"
#include "model/ast_metadata/AstMetadata.h"


/**
    Implementation may throw EulException on fatal error.
    It can also call log.error, lor.ward and log.info to communicate messages to the user.
*/
using CodeGenerator = std::function<
    void(const AstRoot* ast, const AstMetadata* astMetadata, EulLogger* log)
>;
