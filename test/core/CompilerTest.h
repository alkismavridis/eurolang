
void CompilerTest_init(char* t) {
    //1. create the compiler
    Compiler comp;
    void (*onError)(Compiler *this) = ({void __fn__(Compiler *this){ return; } __fn__; });
    Compiler_init(&comp, onError);

    //assert values
    assertPtrEquals(onError, comp.onError, t, "A1");
    assertIntEquals(ErrorType_NO_ERROR, comp.errorCode, t, "A2");
    assertNull(comp.errorMessage, t, "A3");
    assertNotNull(comp.stringBuffer, t, "A4");
    assertIntEquals(0, comp.stringBufferIndex, t, "A5");
    assertNull(comp.currentSource, t, "A6");
    assertIntEquals(0, EulNodeList_length(&comp.program.sources), t, "A7");

    Compiler_deinit(&comp);
}


void CompilerTest_reset(char* t) {
    //1, init a compiler
    Compiler comp;
    Compiler_init(&comp, 0);

    //2. add stuff to the compiler
    comp.errorCode = 97;
    comp.errorMessage = "hello";
    comp.stringBufferIndex = 55;

    EulToken *file1 = EulProgram_getSource(&comp.program, "someFileName1.eul", 1);
    EulToken *file2 = EulProgram_getSource(&comp.program, "someFileName2.eul", 1);
    comp.currentSource = file2->value.asSourceFile;

    //3. call reset
    Compiler_reset(&comp);


    //4. make assertions
    assertIntEquals(ErrorType_NO_ERROR, comp.errorCode, t, "A1");
    assertNull(comp.errorMessage, t, "A2");
    assertNotNull(comp.stringBuffer, t, "A3");
    assertIntEquals(0, comp.stringBufferIndex, t, "A4");
    assertNull(comp.currentSource, t, "A5");
    assertIntEquals(0, EulNodeList_length(&comp.program.sources), t, "A6");

    Compiler_deinit(&comp);
}


void CompilerTest_errors(char* t) {
    int errorCount = 0;
    void (*onError)(Compiler *this) = ({void __fn__(Compiler *this){ errorCount++; } __fn__; });
    Compiler comp;
    Compiler_init(&comp, onError);

    //1. make a lexer error
    Compiler_makeLexerError(&comp, "lex");
    assertIntEquals(ErrorType_LEXER, comp.errorCode, t, "A1");
    assertStringEquals("lex", comp.errorMessage, t, "A2");
    assertIntEquals(1, errorCount, t, "A3");

    //2. make a parser error
    Compiler_makeFileNotFoundError(&comp, "file not found");
    assertIntEquals(ErrorType_FILE_NOT_FOUND, comp.errorCode, t, "B1");
    assertStringEquals("file not found", comp.errorMessage, t, "B2");
    assertIntEquals(2, errorCount, t, "B3");

    //3 clear the error
    Compiler_clearError(&comp);
    assertIntEquals(ErrorType_NO_ERROR, comp.errorCode, t, "C1");
    assertNull(comp.errorMessage, t, "C2");
    assertIntEquals(2, errorCount, t, "C3");



    //2. make a semantics error
    Compiler_makeSemanticError(&comp, "semantic");
    assertIntEquals(ErrorType_SEMANTIC, comp.errorCode, t, "D1");
    assertStringEquals("semantic", comp.errorMessage, t, "D2");
    assertIntEquals(3, errorCount, t, "D3");

    Compiler_deinit(&comp);
}



void CompilerTest_buffers(char* t) {
    //TODO
}


void CompilerTest_compile(char* t) {
    Compiler comp;
    Compiler_init(&comp, 0);

    //1. Compile an empty source file
    Compiler_compile(
        &comp,
        EulProgram_getSource(&comp.program, "name1.eul", 1)->value.asSourceFile,
        fmemopen ("", 0, "r")
    );
    assertIntEquals(1, EulNodeList_length(&comp.program.sources), t, "A1");
    assertNotNull(EulProgram_getSource(&comp.program, "name1.eul", 0), t, "A2");
    assertTrue(EulProgram_getSource(&comp.program, "name1.eul", 0)->value.asSourceFile->isParsed, t, "A3");

    //2 Compile a second one
    char* txt = "14u";
    Compiler_compile(
        &comp,
        EulProgram_getSource(&comp.program, "name2.eul", 1)->value.asSourceFile,
        fmemopen (txt, strlen(txt), "r")
    );
    assertIntEquals(2, EulNodeList_length(&comp.program.sources), t, "B1");
    assertNotNull(EulProgram_getSource(&comp.program, "name2.eul", 0), t, "B2");
    assertTrue(EulProgram_getSource(&comp.program, "name2.eul", 0)->value.asSourceFile->isParsed, t, "B3");

    Compiler_deinit(&comp);
}





void CompilerTest_runAllTests() {
  CompilerTest_init("CompilerTest_init");
  CompilerTest_reset("CompilerTest_reset");
  CompilerTest_errors("CompilerTest_errors");
  CompilerTest_buffers("CompilerTest_buffers");
  CompilerTest_buffers("CompilerTest_compile");
}
