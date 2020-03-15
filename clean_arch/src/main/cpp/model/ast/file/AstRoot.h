#pragma once

#include <list>
#include <memory>
#include "model/ast/statements/EulStatement.h"
#include "model/ast/statements/ScopeRoot.h"

struct AstRoot : public ScopeRoot {
	const std::string name;
	const std::list<std::unique_ptr<const EulStatement>> statements;

	AstRoot(std::string& name, std::list<std::unique_ptr<const EulStatement>> statements);
};
