#include "EulCompiler.h"
#include "analyser/parse/AstAnalyser.h"

using namespace std;

void EulCompiler::compile()  {
    try {
        unique_ptr<const AstRoot> ast = this->astProvider->get( this->options->sourceFileName, this->log );
        if(this->log->hasErrors()) {
            return;
        }

        EulScope globalScope(nullptr);
        unique_ptr<const AstMetadata> astMetadata = AstAnalyser::analyse(&globalScope);

        if(this->log->hasErrors()) {
            return;
        }

        this->codeGenerator->consume(ast.get(), astMetadata.get(), this->log);
    }
    catch(EulException& ex) {
        log->error(ex);
    }
}
