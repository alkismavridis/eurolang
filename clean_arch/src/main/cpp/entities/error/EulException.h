#pragma once

#include <string>

struct EulException {
  const std::string className;
  const std::string message;

  EulException(const std::string& className, const std::string& message);
};
