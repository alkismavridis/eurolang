#pragma once


class CompilerTest {
    public: static void constructorTest(const std::string& t) {
        //1. create the compiler
        void(*errorHandler)(Compiler*) = [](Compiler* ths) { return; };
        Compiler comp(errorHandler);

        //assert values
        Assert::equals((void*)errorHandler, (void*)comp.onError, t + "A1");
        Assert::null(comp.currentSource, t + "A2");
        Assert::equals(0, comp.errors.size(), t + "A3");
        Assert::equals(0, comp.program.sources.size(), t + "A5");
        Assert::equals("", comp.buffer, t + "A6");
    }



    public: static void resetTest(const std::string& t) {
        //1, init a compiler
        Compiler comp(0);

        //2. add stuff to the compiler
        comp.addError(EulErrorType::LEXER, "hello");
        comp.buffer.assign("12345");

        EulSourceFile *file1 = comp.program.getSource("someFileName1.eul", 1);
        EulSourceFile *file2 = comp.program.getSource("someFileName2.eul", 1);
        comp.currentSource = file2;

        //3. call reset
        comp.reset();

        //4. make assertions
        Assert::equals(0, comp.errors.size(), t + "A1");
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

        //1. make a lexer error, including error handler, using 2-params constructor
        comp.addError(EulErrorType::LEXER, "lex");
        Assert::equals(1, comp.errors.size(), t + "A1");
        Assert::equals(EulErrorType::LEXER, comp.errors[0]->type, t + "A2");
        Assert::equals("lex", comp.errors[0]->message, t + "A3");
        Assert::equals(".", comp.buffer, t + "A4");

        //2. make a parser error, including error handler, using 1-param constructor
        comp.addError(EulError(EulErrorType::SYNTAX, "file not found"));
        Assert::equals(2, comp.errors.size(), t + "B1");
        Assert::equals(EulErrorType::SYNTAX, comp.errors[1]->type, t + "B2");
        Assert::equals("file not found", comp.errors[1]->message, t + "B3");
        Assert::equals("..", comp.buffer, t + "B4");

        //3 clear the error, including error handler
        comp.clearErrors();
        Assert::equals(0, comp.errors.size(), t + "C1");
        Assert::equals("..", comp.buffer, t + "C3");

        //Test without an error handler
        comp.reset();
        comp.onError = 0;

        //5. make a lexer error, without error handler, using 2-params constructor
        comp.addError(EulErrorType::LEXER, "lex");
        Assert::equals(1, comp.errors.size(), t + "E1");
        Assert::equals(EulErrorType::LEXER, comp.errors[0]->type, t + "E2");
        Assert::equals("lex", comp.errors[0]->message, t + "E3");
        Assert::equals("", comp.buffer, t + "E4");

        //6. make a parser error, without error handler, using 1-param constructor
        comp.addError(EulError(EulErrorType::SYNTAX, "file not found"));
        Assert::equals(2, comp.errors.size(), t + "F1");
        Assert::equals(EulErrorType::SYNTAX, comp.errors[1]->type, t + "F2");
        Assert::equals("file not found", comp.errors[1]->message, t + "F3");
        Assert::equals("", comp.buffer, t + "F4");

        //7. clear the error, without error handler
        comp.clearErrors();
        Assert::equals(0, comp.errors.size(), t + "G1");
        Assert::equals("", comp.buffer, t + "G2");
    }





    public: static void runAll() {
        constructorTest("CompilerTest.constructorTest ");
        resetTest("CompilerTest.resetTest ");
        compileTest("CompilerTest.compileTest ");
        errorGenerationTest("CompilerTest.errorGenerationTest ");
    }
};
