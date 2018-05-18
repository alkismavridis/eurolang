#pragma once



//region UTIL FUNCTIONS
void SyntaxTest_parseString(Compiler *compiler, char* source) {
  yyrestart( fmemopen (source, strlen (source), "r"), compiler->scanner );
	yyset_lineno(1, compiler->scanner);
  yyparse(compiler->scanner, compiler);
}
//endregion



//region TESTS
void SyntaxTest_topLevelTest(char* t) {
  //Compiler compiler;
	//Compiler_init(&compiler, 0);


  //SyntaxTest_parseString(&compiler, "var x=5; var y=6;");


  //Compiler_deinit(&compiler);
}
//endregion



void SyntaxTest_runAllTests() {
  //yydebug = 1;
	//SyntaxTest_topLevelTest("SyntaxTest_topLevelTest");
}
