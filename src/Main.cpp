//region EXTERNAL IMPORTS
#include <iostream>
#include <forward_list>
#include <sstream>
#include <map>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/Optional.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
//endregion



//region APP HEADERS
#include "../src/constants/Constants.h"

#include "../src/core/EulToken/EulTokenType.h"
#include "../src/core/EulToken/EulToken.h"
#include "../src/core/EulToken/EulIntToken.h"
#include "../src/core/EulToken/EulCharToken.h"
#include "../src/core/EulToken/EulFloatToken.h"
#include "../src/core/EulToken/EulIdToken.h"
#include "../src/core/EulToken/EulStringToken.h"

#include "../src/core/EulAst/EulAstType.h"
#include "../src/core/EulAst/EulAst.h"
#include "../src/core/EulAst/EulType/EulType.h"
#include "../src/core/EulAst/EulSymbol/EulSymbol.h"

#include "../src/core/EulAst/EulStatement/EulStatementType.h"
#include "../src/core/EulAst/EulStatement/EulStatement.h"
#include "../src/core/EulAst/EulStatement/EulImportStatement.h"
#include "../src/core/EulAst/EulStatement/EulExportStatement.h"
#include "../src/core/EulAst/EulDeclaration/VarDeclaration.h"

#include "../src/core/EulSourceFile/EulSourceFile.h"
#include "../src/core/EulProgram/EulProgram.h"
#include "../src/core/Compiler/EulError/EulError.h"
#include "../src/core/Compiler/Compiler.h"
#include "../src/lexer/EulScanner.h"

#include "../src/llvm/EulLlvmExporter.h"
//endregion


#include "../src/cli/EulCliParams/EulCliParams.h"




//region IMPLEMENTATIONS
#include "../src/core/Core.module.h"
#include "../src/llvm/EulLlvmExporter.module.h"
#include "../src/cli/EulcCli.module.h"
//endregion



//region ERROR HANDLING
void handleError(Compiler* comp) {
    //std::cout << comp->error.message << std::endl;
}

void reportErrors(Compiler* comp) {
    for(auto error : comp->errors) std::cout << error << std::endl;
}
//endregion



int main( const int argc, const char **argv ) {

    try {
        EulCliParams params(argc, argv);
        Compiler comp(handleError);
        EulLlvmExporter llvmExporter;

        auto fileEntries = params.inputFiles.begin();
        comp.compile(fileEntries->first, fileEntries->second);


        llvmExporter.produceOutput(&comp, params.outputFile);


        //report errors
        reportErrors(&comp);
    }
    catch(EulError e) {
        std::cout << "Exception happened! " << e.message << std::endl;
        return 1;
    }

    return 0;
}