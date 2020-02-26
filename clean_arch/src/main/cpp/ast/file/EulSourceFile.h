#pragma once

#include <list>
#include <memory>
#include "ast/statements/EulStatement.h"

struct EulSourceFile {
  const std::string name;
  std::list<std::unique_ptr<const EulStatement>> statements;

  EulSourceFile(std::string& name);
};
