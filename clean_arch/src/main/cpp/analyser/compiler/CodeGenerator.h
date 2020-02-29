#pragma once


#include "ast/file/AstRoot.h"
#include "analyser/model/error/EulLogger.h"
#include "analyser/model/meta/AstMetadata.h"

struct CodeGenerator {
    /**
        Implementation may throw EulException on fatal error.
        It can also call log.error, lor.ward and log.info to communicate messages to the user.
    */
    virtual void consume(
        const AstRoot* ast,
        const AstMetadata* astMetadata,
        EulLogger* log
    );
};
