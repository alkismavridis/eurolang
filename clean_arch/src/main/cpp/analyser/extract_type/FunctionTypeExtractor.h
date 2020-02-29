#pragma once

#include <memory>

#include "ast/statements/FunctionDeclarationStatement.h"
#include "analyser/model/types/FunctionType.h"
#include "analyser/model/meta/AstMetadata.h"

struct FunctionTypeExtractor {
    static std::unique_ptr<const FunctionType> extract(
        const FunctionDeclarationStatement* stmt,
        AstMetadata* meta
    );
};
