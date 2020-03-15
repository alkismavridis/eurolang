#include "EulCompiler.h"
#include "SuperGlobals.h"
#include "usecases/parse/AstAnalyser.h"

using namespace std;


void EulCompiler::compile()  {
    try {
        unique_ptr<const AstRoot> ast = this->astProvider( this->options->sourceFileName, this->log );
        if(this->log->hasErrors()) {
            return;
        }

        EulScope globalScope(nullptr);
        unique_ptr<const AstMetadata> astMetadata = AstAnalyser::analyse(&globalScope, &this->superGlobals);
        if(this->log->hasErrors()) {
            return;
        }

        this->codeGenerator(ast.get(), astMetadata.get(), this->log);
    }
    catch(EulException& ex) {
        log->error(ex);
    }
}

 void EulCompiler::declareSuperGlobals(EulScope* globalScope) {
    globalScope->declareType("Any", &this->superGlobals.anyType, AstLocation(-1, -1));
    globalScope->declareType("Boolean", &this->superGlobals.booleanType, AstLocation(-1, -1));
    globalScope->declareType("Void", &this->superGlobals.voidType, AstLocation(-1, -1));

    globalScope->declareType("Char", &this->superGlobals.char8Type, AstLocation(-1, -1));
    globalScope->declareType("Char8", &this->superGlobals.char8Type, AstLocation(-1, -1));
    globalScope->declareType("Char16", &this->superGlobals.char16Type, AstLocation(-1, -1));
    globalScope->declareType("Char32", &this->superGlobals.char32Type, AstLocation(-1, -1));

    globalScope->declareType("Float", &this->superGlobals.float32Type, AstLocation(-1, -1));
    globalScope->declareType("Float64", &this->superGlobals.float64Type, AstLocation(-1, -1));

    globalScope->declareType("Int", &this->superGlobals.int32Type, AstLocation(-1, -1));
    globalScope->declareType("UInt", &this->superGlobals.uInt32Type, AstLocation(-1, -1));
    globalScope->declareType("Int8", &this->superGlobals.int8Type, AstLocation(-1, -1));
    globalScope->declareType("UInt8", &this->superGlobals.uInt8Type, AstLocation(-1, -1));
    globalScope->declareType("Int16", &this->superGlobals.int16Type, AstLocation(-1, -1));
    globalScope->declareType("UInt16", &this->superGlobals.uInt16Type, AstLocation(-1, -1));
    globalScope->declareType("Int32", &this->superGlobals.int32Type, AstLocation(-1, -1));
    globalScope->declareType("UInt32", &this->superGlobals.uInt32Type, AstLocation(-1, -1));
    globalScope->declareType("Int64", &this->superGlobals.int64Type, AstLocation(-1, -1));
    globalScope->declareType("UInt64", &this->superGlobals.uInt64Type, AstLocation(-1, -1));
}
