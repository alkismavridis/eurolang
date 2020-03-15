#pragma once

#include <memory>

#include "model/ast/statements/FunctionDeclarationStatement.h"
#include "model/types/FunctionType.h"
#include "model/ast_metadata/AstMetadata.h"

struct FunctionTypeExtractor {
    static std::unique_ptr<const FunctionType> extract(
        const FunctionDeclarationStatement* stmt,
        AstMetadata* meta
    );
};
