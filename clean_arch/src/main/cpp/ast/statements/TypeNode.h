#pragma once

#include<string>

#include "ast/AstNode.h"

/**
    This class represents a type reference on the AST.
    NOT the type itself.

    To understand the difference, think that there will be multiple TypeNodes that refer to type Int,
    but there is only one actual type Int, defined in the global scope.
*/
struct TypeNode : public AstNode {
    const std::string name;

    TypeNode(const std::string& name, AstLocation location);
};
