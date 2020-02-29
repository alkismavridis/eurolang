#pragma once

#include "analyser/model/meta/AstMetadata.h"

struct AstAnalyser {
    static std::unique_ptr<const AstMetadata> analyse(EulScope* const globalScope);
};
