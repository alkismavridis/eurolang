#pragma once

#include "ast/AstNode.h"

/**
 This represents an actual EUL operator, not its reference on the AST.
 For example, there is one + operator, even if it appears 100 times in a source file.
 This class represents this one operator with its unique attributes.

 Subclasses of this class are effectively singletons.
*/
struct EulOperator {};
