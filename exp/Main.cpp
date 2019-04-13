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
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
//endregion



//region UGGLY, DISGUSTING FORWARD DECLARATIONS
class EulCodeGenContext;
class EulScope;
//endregion




//region APP HEADERS
#include "../src/constants/Constants.h"

#include "../src/core/EulToken/EulTokenType.h"
#include "../src/core/EulToken/EulToken.h"
#include "../src/core/EulToken/EulIntNode.h"
#include "../src/core/EulToken/EulCharNode.h"
#include "../src/core/EulToken/EulFloatNode.h"
#include "../src/core/EulToken/EulSymbolNameNode.h"
#include "../src/core/EulToken/EulStringNode.h"

#include "../src/core/EulAst/EulAstType.h"
#include "../src/core/EulAst/EulAst.h"
#include "../src/core/EulAst/EulType/EulType.h"

#include "../src/core/EulAst/EulStatement/EulStatementType.h"
#include "../src/core/EulAst/EulStatement/EulStatement.h"
#include "../src/core/EulAst/EulStatement/EulImportStatement.h"
#include "../src/core/EulAst/EulStatement/EulExportStatement.h"
#include "../src/core/EulAst/EulStatement/ReturnStatement.h"
#include "../src/core/EulAst/EulDeclaration/VarDeclaration.h"
#include "../src/core/EulAst/EulStatement/VarDeclarationStatement.h"

#include "../src/core/EulScope/EulSymbol.h"
#include "../src/core/EulScope/EulScope.h"
#include "../src/core/EulSourceFile/EulSourceFile.h"
#include "../src/core/EulProgram/EulProgram.h"
#include "../src/core/Compiler/EulError/EulError.h"
#include "../src/core/Compiler/Compiler.h"

#include "../src/llvm/EulCodeGenContext.h"
//endregion


#include "../src/cli/EulCliParams/EulCliParams.h"




//region IMPLEMENTATIONS
//endregion



int main(const int argc, const char **argv) {
    llvm::LLVMContext llvmCtx;
    llvm::Module globalModule("entryPointModule", llvmCtx);



    std::cout << "SIZES\n";
    std::cout << "LLVMContext: " << sizeof(llvmCtx) << "\n";
    std::cout << "Module: " << sizeof(globalModule) << "\n";
    std::cout << "=====================\n\n\n";

    llvm::APInt it1 = llvm::APInt(32, 12345, false);
    auto it2 = it1.sext(64);

    std::cout << it1.getBitWidth() << "   " << it2.getBitWidth() << "\n" ;
    std::cout << it1.getZExtValue() << "   " << it2.getZExtValue() << "\n" ;


    it1 = 5;
    it2 = 8;
    std::cout << it1.getBitWidth() << "   " << it2.getBitWidth() << "\n"     ;
    std::cout << it1.getZExtValue() << "   " << it2.getZExtValue() << "\n" ;


    return 0;
}