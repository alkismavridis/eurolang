#pragma once

#include "analyser/model/error/EulLogger.h"

#include "AstProvider.h"
#include "CodeGenerator.h"
#include "CompileOptions.h"


//Defined in analyser, implemented in infrastructure.cli




class EulCompiler {
    const CompileOptions* const options;
    AstProvider* const astProvider;
    CodeGenerator* const codeGenerator;
    EulLogger* const log;

    public:
    EulCompiler(CompileOptions* options, AstProvider* astProvider, CodeGenerator* codeGenerator, EulLogger* log) :
        options(options),
        astProvider(astProvider),
        codeGenerator(codeGenerator),
        log(log) {}

    //never throws exception.
    void compile();
};
