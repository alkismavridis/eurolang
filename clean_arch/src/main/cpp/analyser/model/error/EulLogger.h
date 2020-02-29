#pragma once

#include "EulException.h"

struct EulLogger {
    // virtual void info(const EulInfo& inf);
    // virtual void warn(const EulWarning& warn);
    virtual void error(const EulException& ex);
    virtual bool hasErrors();
};
