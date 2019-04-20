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
class EulType;
//endregion




//region APP HEADERS
#include "../src/core/Constants.h"


#include "../src/core/EulNode/enums/EulNodeType.h"
#include "../src/core/EulNode/EulNode.h"
#include "../src/core/EulNode/reuseables/ValueNode.h"
#include "../src/core/EulNode/leaf_nodes/EulIntNode/EulIntNode.h"
#include "../src/core/EulNode/leaf_nodes/EulCharNode/EulCharNode.h"
#include "../src/core/EulNode/leaf_nodes/EulBooleanNode/EulBooleanNode.h"
#include "../src/core/EulNode/leaf_nodes/EulFloatNode/EulFloatNode.h"
#include "../src/core/EulNode/leaf_nodes/EulSymbolNameNode/EulSymbolNameNode.h"
#include "../src/core/EulNode/leaf_nodes/EulStringNode/EulStringNode.h"

#include "../src/core/EulNode/enums/EulTypeEnum.h"
#include "../src/core/EulNode/types/EulType/EulType.h"
#include "../src/core/EulNode/types/EulIntegerType/EulIntegerType.h"
#include "../src/core/EulNode/types/EulFloatType/EulFloatType.h"
#include "../src/core/EulNode/types/EulCharType/EulCharType.h"
#include "../src/core/EulNode/types/EulStringType/EulStringType.h"
#include "../src/core/EulNode/types/EulFunctionType/EulFunctionType.h"
#include "../src/core/EulNode/types/EulPointerType/EulPointerType.h"
#include "../src/core/EulNode/types/EulNamedType/EulNamedType.h"
#include "../src/core/EulNode/types/EulVoidType/EulVoidType.h"
#include "../src/core/EulNode/types/EulAnyType/EulAnyType.h"
#include "../src/core/EulNode/types/EulBooleanType/EulBooleanType.h"

#include "../src/core/EulNode/enums/EulStatementType.h"
#include "../src/core/EulNode/statements/EulStatement/EulStatement.h"
#include "../src/core/EulNode/statements/EulImportStatement/EulImportStatement.h"
#include "../src/core/EulNode/statements/EulExportStatement/EulExportStatement.h"
#include "../src/core/EulNode/statements/ReturnStatement/ReturnStatement.h"
#include "../src/core/EulNode/reuseables/VarDeclaration/VarDeclaration.h"
#include "../src/core/EulNode/statements/VarDeclarationStatement/VarDeclarationStatement.h"

#include "../src/core/misc/EulSymbol/EulSymbol.h"
#include "../src/core/misc/EulScope/EulScope.h"
#include "../src/core/EulNode/reuseables/EulCodeBlock/EulCodeBlock.h"
#include "../src/core/EulNode/reuseables/EulFunction/EulFunction.h"
#include "../src/core/EulNode/reuseables/EulExpressionCodeBlock/EulExpressionCodeBlock.h"
#include "../src/core/EulNode/statements/EulIfStatement/EulIfStatement.h"
#include "../src/core/EulNode/statements/EulWhileStatement/EulWhileStatement.h"
#include "../src/core/EulNode/statements/EulFuncDeclarationStatement/EulFuncDeclarationStatement.h"

#include "../src/core/Compiler/EulSourceFile/EulSourceFile.h"
#include "../src/core/Compiler/EulProgram/EulNativeTypes.h"
#include "../src/core/Compiler/EulProgram/EulProgram.h"
#include "../src/core/Compiler/EulError/EulError.h"
#include "../src/core/Compiler/Compiler.h"
#include "../src/lexer/EulScanner.h"

#include "../src/llvm/EulCodeGenFlags.h"
#include "../src/llvm/EulCodeGenContext.h"
//endregion


#include "../src/cli/EulCliParams/EulCliParams.h"
#include "Assert.h"



//region IMPLEMENTATIONS
#include "../src/core/Core.impl.h"
#include "../src/parser/EulParsingUtils.impl.h"
#include "../src/llvm/EulCodeGenContext.module.h"

#include "./core/EulNode/EulTokenTest.h"
#include "./core/EulNode/EulAstTest.h"
#include "./core/misc/EulScope/EulScopeTest.h"
#include "./core/Compiler/EulSourceFile/EulSourceFileTest.h"
#include "./core/Compiler/EulProgram/EulProgramTest.h"
#include "./core/Compiler/CompilerTest.h"

#include "./lexer/EulScannerTest.h"

#include "./parser/EulParserTest.h"
#include "./parser/EulIfStatementTest.h"
#include "./parser/EulWhileStatementTest.h"


#include "./core/EulNode/EulProgramCodegenTest.h"
#include "./core/EulNode/EulTokenCodeGenTest.h"
#include "./core/EulNode/EulAstCodeGenTest.h"
#include "./core/EulNode/EulCodeGenContextTest.h"
#include "./core/EulNode/EulOperatorCodeGenTest.h"
#include "./core/EulNode/EulTypeCodeGenTest.h"
#include "./core/EulNode/IfStatementCodeGenTest.h"
#include "./core/EulNode/WhileStatementCodeGenTest.h"
//endregion



int main() {
    std::cout << "Start running tests...\n";

    //1. Core tests
	EulTokenTest::runAll();
	EulAstTest::runAll();
	EulSourceFileTest::runAll();
	EulProgramTest::runAll();
	CompilerTest::runAll();
	EulScopeTest::runAll();

	//2. Lexer tests
	EulScannerTest::runAll();

    //3. Parser tests
    EulParserTest::runAll();
    EulIfStatementTest::runAll();
    EulWhileStatementTest::runAll();


    //4. Core generation Tests
    EulProgramCodegenTest::runAll();
    EulTokenCodeGenTest::runAll();
    EulAstCodeGenTest::runAll();
    EulCodeGenContextTest::runAll();
    EulOperatorCodeGenTest::runAll();
    EulTypeCodeGenTest::runAll();
    IfStatementCodeGenTest::runAll(); //TODO <------ not done yet
    WhileStatementCodeGenTest::runAll(); //TODO <------ not done yet


    //============ NOT UNIT TESTS =============
    //TODO Compiler.produceOutput test
    //TODO EulProgram.impl.h:  emmitObjCode, emmitIRAssembly



    //============ MINOR IMPORTANCE =============
    //TODO EulSourceFile    parseAST


	std::cout << "All tests passed successfully.\n";
	return 0;
}
