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

#include "../src/core/misc/EulCodeGenContext/EulCodeGenContext.h"
//endregion


#include "../src/cli/EulCliParams/EulCliParams.h"
#include "../src/core/Core.impl.h"
#include "../src/parser/EulParsingUtils.impl.h"
#include "../src/core/misc/EulCodeGenContext/EulCodeGenContext.impl.h"


#include "test_utils/Assert.h"








//region CORE TESTS
#include "core/Compiler/EulProgram/EulProgramTest.h"
#include "core/Compiler/EulSourceFile/EulSourceFileTest.h"
#include "core/Compiler/CompilerTest.h"

#include "core/misc/EulScope/EulScopeTest.h"
#include "core/misc/EulCodeGenContext/EulCodeGenContextTest.h"

#include "core/EulNode/expressions/EulFunctionCallExp/EulFunctionCallExpTest.h"
#include "core/EulNode/expressions/EulInfixExp/EulInfixExpTest.h"
#include "core/EulNode/expressions/EulPrefixExp/EulPrefixExpTest.h"

#include "core/EulNode/leaf_nodes/EulBooleanNode/EulBooleanNodeTest.h"
#include "core/EulNode/leaf_nodes/EulCharNode/EulCharNodeTest.h"
#include "core/EulNode/leaf_nodes/EulFloatNode/EulFloatNodeTest.h"
#include "core/EulNode/leaf_nodes/EulIntNode/EulIntNodeTest.h"
#include "core/EulNode/leaf_nodes/EulStringNode/EulStringNodeTest.h"
#include "core/EulNode/leaf_nodes/EulSymbolNameNode/EulSymbolNameNodeTest.h"

#include "core/EulNode/operators/arithmetic/LeftShiftOperator/LeftShiftOperatorTest.h"
#include "core/EulNode/operators/arithmetic/MinusOperator/MinusOperatorTest.h"
#include "core/EulNode/operators/arithmetic/PercentOperator/PercentOperatorTest.h"
#include "core/EulNode/operators/arithmetic/PlusOperator/PlusOperatorTest.h"
#include "core/EulNode/operators/arithmetic/RightShiftOperator/RightShiftOperatorTest.h"
#include "core/EulNode/operators/arithmetic/SlashOperator/SlashOperatorTest.h"
#include "core/EulNode/operators/arithmetic/StarOperator/StarOperatorTest.h"
#include "core/EulNode/operators/assignments/AssignOperator/AssignOperatorTest.h"
#include "core/EulNode/operators/logical/EqualsOperator/EqualsOperatorTest.h"
#include "core/EulNode/operators/logical/LessEqualsOperator/LessEqualsOperatorTest.h"
#include "core/EulNode/operators/logical/LessOperator/LessOperatorTest.h"
#include "core/EulNode/operators/logical/MoreEqualsOperator/MoreEqualsOperatorTest.h"
#include "core/EulNode/operators/logical/MoreOperator/MoreOperatorTest.h"
#include "core/EulNode/operators/logical/NotOperator/NotOperatorTest.h"
#include "core/EulNode/operators/logical/NotEqualsOperator/NotEqualsOperatorTest.h"
#include "core/EulNode/operators/logical/NotSameOperator/NotSameOperatorTest.h"
#include "core/EulNode/operators/logical/SameOperator/SameOperatorTest.h"

#include "core/EulNode/reuseables/VarDeclaration/VarDeclarationTest.h"
#include "core/EulNode/reuseables/EulFunction/EulFunctionTest.h"
#include "core/EulNode/reuseables/EulCodeBlock/EulCodeBlockTest.h"

#include "core/EulNode/statements/EulExpStatement/EulExpStatementTest.h"
#include "core/EulNode/statements/EulIfStatement/EulIfStatementTest.h"
#include "core/EulNode/statements/EulWhileStatement/EulWhileStatementTest.h"
#include "core/EulNode/statements/ReturnStatement/ReturnStatementTest.h"
#include "core/EulNode/statements/VarDeclarationStatement/VarDeclarationStatementTest.h"
#include "core/EulNode/statements/EulFuncDeclarationStatement/EulFuncDeclarationStatementTest.h"

#include "core/EulNode/types/EulFloatType/EulFloatTypeTest.h"
#include "core/EulNode/types/EulFunctionType/EulFunctionTypeTest.h"
#include "core/EulNode/types/EulIntegerType/EulIntegerTypeTest.h"
#include "core/EulNode/types/EulNamedType/EulNamedTypeTest.h"
#include "core/EulNode/types/EulPointerType/EulPointerTypeTest.h"
#include "core/EulNode/types/EulBooleanType/EulBooleanTypeTest.h"
#include "core/EulNode/types/EulCharType/EulCharTypeTest.h"
#include "core/EulNode/types/EulStringType/EulStringTypeTest.h"
#include "core/EulNode/types/EulType/EulTypeTest.h"
#include "core/EulNode/types/EulAnyType/EulAnyTypeTest.h"
#include "core/EulNode/types/EulVoidType/EulVoidTypeTest.h"
//endregion




//region FLEX-BISON tests
#include "./lexer/EulScannerTest.h"

#include "./parser/EulParserTest.h"
#include "./parser/EulIfStatementParsingTest.h"
#include "./parser/EulWhileStatementParsingTest.h"
//endregion



//region CLI INTERFACE TESTS
#include "cli/EulCliParams/EulCliParamsTest.h"
//endregion




int main() {
  std::cout << "Start running tests...\n";

  //1. Core tests
  EulProgramTest::runAll();
  EulSourceFileTest::runAll();
  CompilerTest::runAll();

  EulScopeTest::runAll();
  EulCodeGenContextTest::runAll();

  EulFunctionCallExpTest::runAll();
  EulInfixExpTest::runAll();
  EulPrefixExpTest::runAll();
  EulBooleanNodeTest::runAll();
  EulCharNodeTest::runAll();
  EulFloatNodeTest::runAll();
  EulIntNodeTest::runAll();
  EulStringNodeTest::runAll();
  EulSymbolNameNodeTest::runAll();



  LeftShiftOperatorTest::runAll();
  MinusOperatorTest::runAll();
  PercentOperatorTest::runAll();
  PlusOperatorTest::runAll();
  RightShiftOperatorTest::runAll();
  SlashOperatorTest::runAll();
  StarOperatorTest::runAll();
  AssignOperatorTest::runAll();
  EqualsOperatorTest::runAll();
  LessEqualsOperatorTest::runAll();
  LessOperatorTest::runAll();
  MoreEqualsOperatorTest::runAll();
  MoreOperatorTest::runAll();
  NotOperatorTest::runAll();
  NotEqualsOperatorTest::runAll();
  NotSameOperatorTest::runAll();
  SameOperatorTest::runAll();

  VarDeclarationTest::runAll();
  EulFunctionTest::runAll();
  EulCodeBlockTest::runAll();

  EulExpStatementTest::runAll();
  EulIfStatementTest::runAll();
  EulWhileStatementTest::runAll();
  ReturnStatementTest::runAll();
  VarDeclarationStatementTest::runAll();
  EulFuncDeclarationStatementTest::runAll();

  EulFloatTypeTest::runAll();
  EulFunctionTypeTest::runAll();
  EulIntegerTypeTest::runAll();
  EulNamedTypeTest::runAll();
  EulPointerTypeTest::runAll();
  EulBooleanTypeTest::runAll();
  EulAnyTypeTest::runAll();
  EulCharTypeTest::runAll();
  EulStringTypeTest::runAll();
  EulVoidTypeTest::runAll();
  EulTypeTest::runAll();


  EulScannerTest::runAll();
  EulParserTest::runAll();
  EulIfStatementParsingTest::runAll();
  EulWhileStatementParsingTest::runAll();

  EulCliParamsTest::runAll();

  std::cout << "\n\n=======================================\n\n\tAll tests passed successfully.\n\n\n";
  return 0;
}
