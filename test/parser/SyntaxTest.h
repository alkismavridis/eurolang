#pragma once



//region UTIL FUNCTIONS

//endregion



//region TESTS
void SyntaxTest_topLevelTest(char* t) {
    Compiler compiler;
    Compiler_init(&compiler, 0);

    char* txt = "var x=5; var y=6; var z=7;";
    printf("TEXT TO PARSE:\n\t%s\n", txt);
    Compiler_compile(
        &compiler,
        EulProgram_getSource(&compiler.program, "name1.eul", 1)->value.asSourceFile,
        fmemopen (txt, strlen(txt), "r")
    );

    assertIntEquals(3, EulNodeList_length(&compiler.currentSource->statements), t, "A1");

    Compiler_deinit(&compiler);
}
//endregion



void SyntaxTest_runAllTests() {
    //yydebug = 1;
    SyntaxTest_topLevelTest("SyntaxTest_topLevelTest");
}
