#pragma once

#include "model/error/EulLogger.h"
#include "model/scope/EulScope.h"

#include "AstProvider.h"
#include "CodeGenerator.h"
#include "CompileOptions.h"
#include "SuperGlobals.h"



class EulCompiler {
    const CompileOptions* const options;
    const AstProvider astProvider;
    const CodeGenerator codeGenerator;
    EulLogger* const log;
    const SuperGlobals superGlobals;


    public:
    EulCompiler(CompileOptions* options, AstProvider astProvider, CodeGenerator codeGenerator, EulLogger* log) :
        options(options),
        astProvider(astProvider),
        codeGenerator(codeGenerator),
        log(log) {}


    //never throws exception.
    void compile();
    void declareSuperGlobals(EulScope* globalScope);
};
