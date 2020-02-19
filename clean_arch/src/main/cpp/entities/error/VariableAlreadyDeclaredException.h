#pragma once

#include <string>
#include "EulException.h"

struct VariableAlreadyDeclaredException : public EulException {
  VariableAlreadyDeclaredException(const std::string& message);
};
