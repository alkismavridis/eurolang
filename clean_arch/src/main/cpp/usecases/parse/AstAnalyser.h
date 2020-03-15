#pragma once

#include "model/ast_metadata/AstMetadata.h"
#include "usecases/compile/SuperGlobals.h"

struct AstAnalyser {
    static std::unique_ptr<const AstMetadata> analyse(
        EulScope* const globalScope,
        const SuperGlobals* const superGlobals
    );
};
