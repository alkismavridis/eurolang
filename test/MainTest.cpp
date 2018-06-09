#include <iostream>
#include <forward_list>
#include <sstream>
#include <map>
#include <cstdlib>
#include <cstring>

#include "Assert.h"

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

#include "../src/core/EulAst/EulStatement/EulStatementType.h"
#include "../src/core/EulAst/EulStatement/EulStatement.h"
#include "../src/core/EulAst/EulStatement/EulImportStatement.h"
#include "../src/core/EulAst/EulStatement/EulExportStatement.h"
#include "../src/core/EulAst/EulSymbol.h"

#include "../src/core/EulSourceFile/EulSourceFile.h"
#include "../src/core/EulProgram/EulProgram.h"
#include "../src/core/Compiler/Compiler.h"

#include "../src/lexer/EulScanner.h"


#include "./core/EulTokenTest.h"
#include "./core/EulSourceFileTest.h"
#include "./core/EulProgramTest.h"
#include "./core/CompilerTest.h"

#include "./lexer/EulScannerTest.h"


int main() {
    //1. Core tests
	EulTokenTest::runAll();
	EulSourceFileTest::runAll();
	EulProgramTest::runAll();
	CompilerTest::runAll();

	//2. Lexer tests
	EulScannerTest::runAll();


    //3. Parser tests


    //4. Core generation Tests

	printf("All tests passed successfully.\n");
	return 0;
}
