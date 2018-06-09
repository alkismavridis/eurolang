#pragma once


class CompilerTest {
    public: static void constructorTest(const std::string& t) {
        //1. create the compiler
        void(*errorHandler)(Compiler*) = [](Compiler* ths) { return; };
        Compiler comp(errorHandler);

        //assert values
        Assert::equals((void*)errorHandler, (void*)comp.onError, t + "A1");
        Assert::null(comp.currentSource, t + "A2");
        Assert::equals(ErrorType_NO_ERROR, comp.errorCode, t + "A3");
        Assert::equals("", comp.errorMessage, t + "A4");
        Assert::equals(0, comp.program.sources.size(), t + "A5");
        Assert::equals("", comp.buffer, t + "A6");
    }



    public: static void resetTest(const std::string& t) {
        //1, init a compiler
        Compiler comp(0);

        //2. add stuff to the compiler
        comp.errorCode = 97;
        comp.errorMessage = "hello";
        comp.buffer.assign("12345");

        EulSourceFile *file1 = comp.program.getSource("someFileName1.eul", 1);
        EulSourceFile *file2 = comp.program.getSource("someFileName2.eul", 1);
        comp.currentSource = file2;

        //3. call reset
        comp.reset();

        //4. make assertions
        Assert::equals(ErrorType_NO_ERROR, comp.errorCode, t + "A1");
        Assert::equals("", comp.errorMessage, t + "A2");
        Assert::equals("", comp.buffer, t + "A3");
        Assert::null(comp.currentSource, t + "A5");
        Assert::equals(0, comp.program.sources.size(), t + "A6");
    }


    public: static void compileTest(const std::string& t) {
        Compiler comp(0);

        //1. Compile an empty source file
        std::stringstream stream = std::stringstream("");
        comp.compile(
            comp.program.getSource("name1.eul", 1),
            &stream
        );

        Assert::equals(1, comp.program.sources.size(), t + "A1");
        Assert::notNull(comp.program.getSource("name1.eul", 0), t + "A2");
        Assert::that(comp.program.getSource("name1.eul", 0)->isParsed, t + "A3");

        //2 Compile a second one
        stream = std::stringstream("");
        comp.compile(
            comp.program.getSource("name2.eul", 1),
            &stream
        );
        Assert::equals(2, comp.program.sources.size(), t + "B1");
        Assert::notNull(comp.program.getSource("name2.eul", 0), t + "B2");
        Assert::that(comp.program.getSource("name2.eul", 0)->isParsed, t + "B3");


        //3. try the string version of compile() method
        stream = std::stringstream("");
        comp.compile("name3.eul", &stream);
        Assert::equals(3, comp.program.sources.size(), t + "C1");
        Assert::notNull(comp.program.getSource("name3.eul", 0), t + "C2");
        Assert::that(comp.program.getSource("name3.eul", 0)->isParsed, t + "C3");
    }



    public: static void errorGenerationTest(const std::string& t) {
        void(*errorHandler)(Compiler*) = [](Compiler* ths) { ths->buffer+="."; };
        Compiler comp(errorHandler);

        //1. make a lexer error, including error handler
        comp.makeLexerError("lex");
        Assert::equals(ErrorType_LEXER, comp.errorCode, t + "A1");
        Assert::equals("lex", comp.errorMessage, t + "A2");
        Assert::equals(".", comp.buffer, t + "A3");

        //2. make a parser error, including error handler
        comp.makeFileNotFoundError("file not found");
        Assert::equals(ErrorType_FILE_NOT_FOUND, comp.errorCode, t + "B1");
        Assert::equals("file not found", comp.errorMessage, t + "B2");
        Assert::equals("..", comp.buffer, t + "B3");

        //3 clear the error, including error handler
        comp.clearError();
        Assert::equals(ErrorType_NO_ERROR, comp.errorCode, t + "C1");
        Assert::equals("", comp.errorMessage, t + "C2");
        Assert::equals("..", comp.buffer, t + "C3");

        //4. make a semantics error, including error handler
        comp.makeSemanticError("semantic");
        Assert::equals(ErrorType_SEMANTIC, comp.errorCode, t + "D1");
        Assert::equals("semantic", comp.errorMessage, t + "D2");
        Assert::equals("...", comp.buffer, t + "D3");


        //Test without an error handler
        comp = Compiler(0);

        //5. make a lexer error, without error handler
        comp.makeLexerError("lex");
        Assert::equals(ErrorType_LEXER, comp.errorCode, t + "E1");
        Assert::equals("lex", comp.errorMessage, t + "E2");
        Assert::equals("", comp.buffer, t + "E3");

        //6. make a parser error, without error handler
        comp.makeFileNotFoundError("file not found");
        Assert::equals(ErrorType_FILE_NOT_FOUND, comp.errorCode, t + "F1");
        Assert::equals("file not found", comp.errorMessage, t + "F2");
        Assert::equals("", comp.buffer, t + "F3");

        //7. clear the error, without error handler
        comp.clearError();
        Assert::equals(ErrorType_NO_ERROR, comp.errorCode, t + "G1");
        Assert::equals("", comp.errorMessage, t + "G2");
        Assert::equals("", comp.buffer, t + "G3");

        //8. make a semantics error, without error handler
        comp.makeSemanticError("semantic");
        Assert::equals(ErrorType_SEMANTIC, comp.errorCode, t + "H1");
        Assert::equals("semantic", comp.errorMessage, t + "H2");
        Assert::equals("", comp.buffer, t + "H3");
    }





    public: static void runAll() {
        constructorTest("CompilerTest.constructorTest ");
        resetTest("CompilerTest.resetTest ");
        compileTest("CompilerTest.compileTest ");
        errorGenerationTest("CompilerTest.errorGenerationTest ");
    }
};
