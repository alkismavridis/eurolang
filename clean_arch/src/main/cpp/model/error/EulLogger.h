#pragma once

#include "EulException.h"

struct EulLogger {
    // virtual void info(const EulInfo& inf);
    // virtual void warn(const EulWarning& warn);
    virtual void error(const EulException& ex) = 0;
    virtual bool hasErrors() = 0;
};
