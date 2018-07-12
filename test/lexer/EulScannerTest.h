#pragma once




class EulScannerTest {

    //region UTIL FUNCTIONS
    private: static void checkIntToken(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, unsigned long expected, unsigned char size, char isUnsigned, const std::string &label) {
    	yy::EulParser::semantic_type semantic;

    	int type = scanner.yylex(&semantic, loc, ctx);
    	Assert::equals(yy::EulParser::token::INT, type, label + "__1");

    	EulIntToken* token = semantic.as<EulIntToken*>();
    	Assert::equals(expected, token->value, label + "__2");
    	Assert::equals(size, token->size, label + "__3");
    	Assert::equals(isUnsigned, token->isUnsigned, label + "__4");

    	semantic.destroy<EulIntToken*>();
    }

    private: static void checkFloatToken(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, double expected, unsigned char size, double tolerance, const std::string &label) {
    	yy::EulParser::semantic_type semantic;

    	int type = scanner.yylex(&semantic, loc, ctx);
    	Assert::equals(yy::EulParser::token::FLOAT, type, label + "__1");

        EulFloatToken* token = semantic.as<EulFloatToken*>();
    	Assert::equals(expected, token->value, tolerance, label + "__2");
    	Assert::equals(size, token->size, label + "__3");

    	semantic.destroy<EulFloatToken*>();
    }

    private: static void checkCharToken(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, unsigned long int expected, unsigned char size, const std::string &label) {
        yy::EulParser::semantic_type semantic;

        int type = scanner.yylex(&semantic, loc, ctx);
    	Assert::equals(yy::EulParser::token::CHAR, type, label + "__type");

        EulCharToken* token = semantic.as<EulCharToken*>();
    	Assert::equals(expected, token->value, label + "__value");
    	Assert::equals(size, token->size, label + "__size");

    	semantic.destroy<EulCharToken*>();
    }

    private: static void checkStringToken(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, const std::string& expected, const std::string &label) {
        yy::EulParser::semantic_type semantic;

        int type = scanner.yylex(&semantic, loc, ctx);
    	Assert::equals(yy::EulParser::token::STRING, type, label + "__1");

        EulStringToken* token = semantic.as<EulStringToken*>();
        Assert::equals(expected, token->value, label + "__2");

        semantic.destroy<EulStringToken*>();
    }

    private: static void checkIdToken(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, const std::string &name, const std::string &label) {
        yy::EulParser::semantic_type semantic;

        int type = scanner.yylex(&semantic, loc, ctx);
        Assert::equals(yy::EulParser::token::ID, type, label + "__1");

        EulIdToken* token = semantic.as<EulIdToken*>();
        Assert::equals(name, token->name, label + "__2");

        semantic.destroy<EulIdToken*>();
    }


   private: static void checkTokenType(EulScanner &scanner, EulParsingContext *ctx, yy::EulParser::location_type* loc, int expected, const std::string &label) {
        yy::EulParser::semantic_type semantic;

        int type = scanner.yylex(&semantic, loc, ctx);
        Assert::equals(expected, type, label + "__1");
   }

   private: static void checkLocation(yy::EulParser::location_type* loc, unsigned int startLine, unsigned int startCol, unsigned int endLine, unsigned int endCol, const std::string &label) {
        Assert::equals(startLine, loc->begin.line, label + "__startLine");
        Assert::equals(startCol, loc->begin.column, label + "__startColumn");
        Assert::equals(endLine, loc->end.line, label + "__endLine");
        Assert::equals(endCol, loc->end.column, label + "__endColumn");
   }
    //endregion




    //region COMMENTS PARSING
   private: static void multiLineCommentTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;

        std::stringstream stream = std::stringstream("123/*hello\n*1/2*3*/world");
        EulScanner scanner(&stream);
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "A1");
        checkLocation(&loc, 1, 1, 1, 4, t + "A1_loc");
        checkIdToken(scanner, &ctx, &loc, "world", t + "A2");
        checkLocation(&loc, 2, 9, 2, 14, t + "A2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::END, t + "A3");

        //start at the end of the line. Change line during ***
        stream = std::stringstream("123/*\n*1/2***\n3*/abc\n12");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "B1");
        checkLocation(&loc, 1, 1, 1, 4, t + "B1_loc");
        checkIdToken(scanner, &ctx, &loc, "abc", t + "B2");
        checkLocation(&loc, 3, 4, 3, 7, t + "B2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "B3");
        checkLocation(&loc, 3, 7, 4, 1, t + "B3_loc");
        checkIntToken(scanner, &ctx, &loc, 12, 4, 0, t + "B4");
        checkLocation(&loc, 4, 1, 4, 3, t + "B4_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::END, t + "B5");

        //no content comment
        stream = std::stringstream(";/**/world12");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::SEMICOLON, t + "C1");
        checkLocation(&loc, 1, 1, 1, 2, t + "C1_loc");
        checkIdToken(scanner, &ctx, &loc, "world12", t + "C2");
        checkLocation(&loc, 1, 6, 1, 13, t + "C2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::END, t + "C3");

        //end of file while parsing. This must generate an appropriate error.
        compiler.clearErrors();
        stream = std::stringstream("123/*\nabcdefgh\n12");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "D2");
        checkLocation(&loc, 1, 1, 1, 4, t + "D2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "D3");


        Assert::equals(1, compiler.errors.size(), t + "D4");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "D4");
        Assert::equals("End of file while parsing comment", compiler.errors[0]->message, t + "D5");
   }


   private: static void singleLineCommentTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;


        //skip comments
        std::stringstream stream = std::stringstream("123//comment1\nend++");
        EulScanner scanner(&stream);

        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "A1");
        checkLocation(&loc, 1, 1, 1, 4, t + "A1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "A2");
        checkLocation(&loc, 1, 4, 2, 1, t + "A2_loc");
        checkIdToken(scanner, &ctx, &loc, "end", t + "A3");

        //meet EOF during single line token. This should be allowed and just return the EOF.
        stream = std::stringstream("123//comment1");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t +"B1");
        checkLocation(&loc, 1, 1, 1, 4, t + "B1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "B2");
        checkLocation(&loc, 1, 4, 2, 1, t + "B2_loc");
   }
    //endregion




    //region NUMBER PARSING
    private: static void parseIntegerTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;

        //end at EOF
        std::stringstream stream = std::stringstream("1");
        EulScanner scanner(&stream);
        checkIntToken(scanner, &ctx, &loc, 1, 4, 0, t + "A1");
        checkLocation(&loc, 1, 1, 1, 2, t + "A1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::END, t + "A2");

        //end at space
        stream = std::stringstream("123 ");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "B1");
        checkLocation(&loc, 1, 1, 1, 4, t + "B1_loc");

        //end at operator
        stream = std::stringstream("123=");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "C1");
        checkLocation(&loc, 1, 1, 1, 4, t + "C1_loc");

        //end at letter other that casting
        stream = std::stringstream("123p");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "D1");
        checkLocation(&loc, 1, 1, 1, 4, t + "D1_loc");


        //cast size
        stream = std::stringstream("123s8");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 123, 8, 0, t + "E1");
        checkLocation(&loc, 1, 1, 1, 6, t + "E1_loc");


        //unsigned literal, stop at operator, and then at space
        stream = std::stringstream("5u123+52u2 ");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 5, 123, 1, t + "F1");
        checkLocation(&loc, 1, 1, 1, 6, t + "F1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "F2");
        checkLocation(&loc, 1, 6, 1, 7, t + "F2_loc");
        checkIntToken(scanner, &ctx, &loc, 52, 2, 1, t + "F3");
        checkLocation(&loc, 1, 7, 1, 11, t + "F3_loc");

        //default sizes. Stop at operator, at space, at letter, at EOF
        stream = std::stringstream("5u+52s 5sa 5u");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 5, 4, 1, t + "G1");
        checkLocation(&loc, 1, 1, 1, 3, t + "G1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "G2");
        checkLocation(&loc, 1, 3, 1, 4, t + "G2_loc");
        checkIntToken(scanner, &ctx, &loc, 52, 4, 0, t + "G3");
        checkLocation(&loc, 1, 4, 1, 7, t + "G3_loc");
        checkIntToken(scanner, &ctx, &loc, 5, 4, 0, t + "G4");
        checkLocation(&loc, 1, 8, 1, 10, t + "G4_loc");
        checkIdToken(scanner, &ctx, &loc, "a", t + "G5");
        checkLocation(&loc, 1, 10, 1, 11, t + "G5_loc");
        checkIntToken(scanner, &ctx, &loc, 5, 4, 1, t + "G6");
        checkLocation(&loc, 1, 12, 1, 14, t + "G6_loc");

        //test zero starting
        stream = std::stringstream("0 0u 0s 0u123 0s123 0+0u12+0s");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 0, 4, 0, t + "H1"); //0
        checkLocation(&loc, 1, 1, 1, 2, t + "H1_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 4, 1, t + "H2"); //0u
        checkLocation(&loc, 1, 3, 1, 5, t + "H2_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 4, 0, t + "H3"); //0s
        checkLocation(&loc, 1, 6, 1, 8, t + "H3_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 123, 1, t + "H4"); //0u123
        checkLocation(&loc, 1, 9, 1, 14, t + "H4_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 123, 0, t + "H5"); //0s123
        checkLocation(&loc, 1, 15, 1, 20, t + "H5_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 4, 0, t + "H6"); //0
        checkLocation(&loc, 1, 21, 1, 22, t + "H6_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "H7"); //+
        checkLocation(&loc, 1, 22, 1, 23, t + "H7_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 12, 1, t + "H8"); //0u12
        checkLocation(&loc, 1, 23, 1, 27, t + "H8_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "H9"); //+
        checkLocation(&loc, 1, 27, 1, 28, t + "H9_loc");
        checkIntToken(scanner, &ctx, &loc, 0, 4, 0, t + "H10"); //0s
        checkLocation(&loc, 1, 28, 1, 30, t + "H10_loc");
    }


    private: static void parseFloatTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;


        //int and float part present
        std::stringstream stream = std::stringstream("0.0+1.0 123.456hello 1.2");
        EulScanner scanner(&stream);
        checkFloatToken(scanner, &ctx, &loc, 0.0, 8, 0.00000001, t + "A1");
        checkLocation(&loc, 1, 1, 1, 4, t + "A1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "A2");
        checkLocation(&loc, 1, 4, 1, 5, t + "A2_loc");
        checkFloatToken(scanner, &ctx, &loc, 1.0, 8, 0.00000001, t + "A3");
        checkLocation(&loc, 1, 5, 1, 8, t + "A3_loc");
        checkFloatToken(scanner, &ctx, &loc, 123.456, 8, 0.00000001, t + "A4");
        checkLocation(&loc, 1, 9, 1, 16, t + "A4_loc");
        checkIdToken(scanner, &ctx, &loc, "hello", t + "A5");
        checkLocation(&loc, 1, 16, 1, 21, t + "A5_loc");
        checkFloatToken(scanner, &ctx, &loc, 1.2, 8, 0.00000001, t + "A6");
        checkLocation(&loc, 1, 22, 1, 25, t + "A6_loc");

        //int part missing, or float part missing
        stream = std::stringstream("0. 123.+.123 1.hello 2.");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkFloatToken(scanner, &ctx, &loc, 0.0, 8, 0.00000001, t + "B1");
        checkLocation(&loc, 1, 1, 1, 3, t + "B1_loc");
        checkFloatToken(scanner, &ctx, &loc, 123.0, 8, 0.00000001, t + "B2");
        checkLocation(&loc, 1, 4, 1, 8, t + "B2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "B3");
        checkLocation(&loc, 1, 8, 1, 9, t + "B3_loc");
        checkFloatToken(scanner, &ctx, &loc, 0.123, 8, 0.00000001, t + "B4");
        checkLocation(&loc, 1, 9, 1, 13, t + "B4_loc");
        checkFloatToken(scanner, &ctx, &loc, 1.0, 8, 0.00000001, t + "B5");
        checkLocation(&loc, 1, 14, 1, 16, t + "B5_loc");
        checkIdToken(scanner, &ctx, &loc, "hello", t + "B6");
        checkLocation(&loc, 1, 16, 1, 21, t + "B6_loc");
        checkFloatToken(scanner, &ctx, &loc, 2.0, 8, 0.00000001, t + "B7");
        checkLocation(&loc, 1, 22, 1, 24, t + "B7_loc");


        //casting with size
        stream = std::stringstream("0f7 1f32+1.f4 .4f12 = 3.3f12");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkFloatToken(scanner, &ctx, &loc, 0, 7, 0.00000001, t + "C1");
        checkLocation(&loc, 1, 1, 1, 4, t + "C1_loc");
        checkFloatToken(scanner, &ctx, &loc, 1, 32, 0.00000001, t + "C2");
        checkLocation(&loc, 1, 5, 1, 9, t + "C2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "C3");
        checkLocation(&loc, 1, 9, 1, 10, t + "C3_loc");
        checkFloatToken(scanner, &ctx, &loc, 1, 4, 0.00000001, t + "C4");
        checkLocation(&loc, 1, 10, 1, 14, t + "C4_loc");
        checkFloatToken(scanner, &ctx, &loc, 0.4, 12, 0.00000001, t + "C5");
        checkLocation(&loc, 1, 15, 1, 20, t + "C5_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN, t + "C6");
        checkLocation(&loc, 1, 21, 1, 22, t + "C6_loc");
        checkFloatToken(scanner, &ctx, &loc, 3.3, 12, 0.00000001, t + "C7");
        checkLocation(&loc, 1, 23, 1, 29, t + "C7_loc");

        //casting default size
        stream = std::stringstream("0f 1f+1.f .4f = 3.3f");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkFloatToken(scanner, &ctx, &loc, 0, 8, 0.00000001, t + "D1");
        checkLocation(&loc, 1, 1, 1, 3, t + "D1_loc");
        checkFloatToken(scanner, &ctx, &loc, 1, 8, 0.00000001, t + "D2");
        checkLocation(&loc, 1, 4, 1, 6, t + "D2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "D3");
        checkLocation(&loc, 1, 6, 1, 7, t + "D3_loc");
        checkFloatToken(scanner, &ctx, &loc, 1.0, 8, 0.00000001, t + "D4");
        checkLocation(&loc, 1, 7, 1, 10, t + "D4_loc");
        checkFloatToken(scanner, &ctx, &loc, 0.4, 8, 0.00000001, t + "D5");
        checkLocation(&loc, 1, 11, 1, 14, t + "D5_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN, t + "D6");
        checkLocation(&loc, 1, 15, 1, 16, t + "D6_loc");
        checkFloatToken(scanner, &ctx, &loc, 3.3, 8, 0.00000001, t + "D7");
        checkLocation(&loc, 1, 17, 1, 21, t + "D7_loc");
    }
    //endregion




    //region TEXT
    private: static void parseIdTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;

    	//int and float part present
    	std::stringstream stream = std::stringstream("hello123__ par123+hello_");
        EulScanner scanner(&stream);
    	checkIdToken(scanner, &ctx, &loc, "hello123__", t + "A1");
    	checkLocation(&loc, 1, 1, 1, 11, t + "A1_loc");
    	checkIdToken(scanner, &ctx, &loc, "par123", t + "A2");
    	checkLocation(&loc, 1, 12, 1, 18, t + "A2_loc");
    	checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "A3");
    	checkLocation(&loc, 1, 18, 1, 19, t + "A3_loc");
    	checkIdToken(scanner, &ctx, &loc, "hello_", t + "A4");
    	checkLocation(&loc, 1, 19, 1, 25, t + "A4_loc");
    }


    private: static void parseCharTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;

        //1 byte long unicodes
        std::stringstream stream = std::stringstream("'b' 'n'+'''");
        EulScanner scanner(&stream);
        checkCharToken(scanner, &ctx, &loc, 'b', 1, t + "A1");
        checkLocation(&loc, 1, 1, 1, 4, t + "A1_loc");
        checkCharToken(scanner, &ctx, &loc, 'n', 1, t + "A2");
        checkLocation(&loc, 1, 5, 1, 8, t + "A2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "A3");
        checkLocation(&loc, 1, 8, 1, 9, t + "A3_loc");
        checkCharToken(scanner, &ctx, &loc, '\'', 1, t + "A4");
        checkLocation(&loc, 1, 9, 1, 12, t + "A4_loc");

        //2 byte long unicodes
        stream = std::stringstream("'ώ' 'ϋ' 'π' 'ü'");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkCharToken(scanner, &ctx, &loc, 0xcf8e, 2, t + "B1");
        checkLocation(&loc, 1, 1, 1, 5, t + "B1_loc");
        checkCharToken(scanner, &ctx, &loc, 0xcf8b, 2, t + "B2");
        checkLocation(&loc, 1, 6, 1, 10, t + "B2_loc");
        checkCharToken(scanner, &ctx, &loc, 0xcf80, 2, t + "B3");
        checkLocation(&loc, 1, 11, 1, 15, t + "B3_loc");
        checkCharToken(scanner, &ctx, &loc, 0xc3bc, 2, t + "B4");
        checkLocation(&loc, 1, 16, 1, 20, t + "B4_loc");

        //4 byte long unicodes
        stream = std::stringstream("'𠜎' '𡇙' '😌' '🙋'");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkCharToken(scanner, &ctx, &loc, 0xf0a09c8e, 4, t + "C1");
        checkLocation(&loc, 1, 1, 1, 7, t + "C1_loc");
        checkCharToken(scanner, &ctx, &loc, 0xf0a18799, 4, t + "C2");
        checkLocation(&loc, 1, 8, 1, 14, t + "C2_loc");
        checkCharToken(scanner, &ctx, &loc, 0xf09f988c, 4, t + "C3");
        checkLocation(&loc, 1, 15, 1, 21, t + "C3_loc");
        checkCharToken(scanner, &ctx, &loc, 0xf09f998b, 4, t + "C4");
        checkLocation(&loc, 1, 22, 1, 28, t + "C4_loc");

        //parse escaped chars
        stream = std::stringstream("'\\n' '\\t' '\\r' '\\f' '\\\\' '\\b' '\\0'");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkCharToken(scanner, &ctx, &loc, '\n', 1, t + "D1");
        checkLocation(&loc, 1, 1, 1, 5, t + "D1_loc");
        checkCharToken(scanner, &ctx, &loc, '\t', 1, t + "D2");
        checkLocation(&loc, 1, 6, 1, 10, t + "D2_loc");
        checkCharToken(scanner, &ctx, &loc, '\r', 1, t + "D3");
        checkLocation(&loc, 1, 11, 1, 15, t + "D3_loc");
        checkCharToken(scanner, &ctx, &loc, '\f', 1, t + "D4");
        checkLocation(&loc, 1, 16, 1, 20, t + "D4_loc");
        checkCharToken(scanner, &ctx, &loc, '\\', 1, t + "D5");
        checkLocation(&loc, 1, 21, 1, 25, t + "D5_loc");
        checkCharToken(scanner, &ctx, &loc, '\b', 1, t + "D6");
        checkLocation(&loc, 1, 26, 1, 30, t + "D6_loc");
        checkCharToken(scanner, &ctx, &loc, '\0', 1, t + "D7");
        checkLocation(&loc, 1, 31, 1, 35, t + "D7_loc");



        //test failed escaped sequenses
        compiler.clearErrors();

        stream = std::stringstream("'\\w'");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "E2");
        checkLocation(&loc, 1, 1, 1, 4, t + "E2_loc");
        Assert::equals(1, compiler.errors.size(), t + "E3");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "E4");
        Assert::equals("Illegal escaped character.", compiler.errors[0]->message, t + "E5");


        //EOF during escaped character
        compiler.clearErrors();

        stream = std::stringstream("'\\");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "F2");
        checkLocation(&loc, 1, 1, 1, 4, t + "F2_loc");
        Assert::equals(1, compiler.errors.size(), t + "F3");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "F4");
        Assert::equals("Illegal escaped character.", compiler.errors[0]->message, t + "F5");


        //To many characters after escaped sequence error
        compiler.clearErrors();

        stream = std::stringstream("'\\nnn'");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "G2");
        checkLocation(&loc, 1, 1, 1, 4, t + "G2_loc");
        Assert::equals(1, compiler.errors.size(), t + "G3");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "G4");
        Assert::equals("Closing ' expected in char literal.", compiler.errors[0]->message, t + "G5");
    }



    private: static void parseStringTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;


        //read simple String and multi line string
        std::stringstream stream = std::stringstream("\"hello world\"123\n\"multi\nline\n\nstring\"end");
        EulScanner scanner(&stream);
        checkStringToken(scanner, &ctx, &loc, "hello world", t + "A1");
        checkLocation(&loc, 1, 1, 1, 14, t + "A1_loc");
        checkIntToken(scanner, &ctx, &loc, 123, 4, 0, t + "A2");
        checkLocation(&loc, 1, 14, 1, 17, t + "A2_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "A3");
        checkLocation(&loc, 1, 17, 2, 1, t + "A3_loc");
        checkStringToken(scanner, &ctx, &loc, "multi\nline\n\nstring", t + "A4");
        checkLocation(&loc, 2, 1, 5, 8, t + "A4_loc");
        checkIdToken(scanner, &ctx, &loc, "end", t + "A5");
        checkLocation(&loc, 5, 8, 5, 11, t + "A5_loc");

        //test escaped characters
        stream = std::stringstream("\"start escaped\\n123\\tabc\\rhello\\fworld\n\\\\backslashes\\bxyz\"end");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkStringToken(scanner, &ctx, &loc, "start escaped\n123\tabc\rhello\fworld\n\\backslashes\bxyz", t + "B1");
        checkLocation(&loc, 1, 1, 2, 20, "B1_loc");
        checkIdToken(scanner, &ctx, &loc, "end", t + "B2");
        checkLocation(&loc, 2, 20, 2, 23, "B2_loc");

        //EOF during string parsing
        compiler.clearErrors();
        Assert::equals(0, compiler.errors.size(), t + "C1");

        stream = std::stringstream("\" End of file will be found before string is closed.");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "C2");
        checkLocation(&loc, 1, 1, 1, 53, t + "C2_loc");
        Assert::equals(1, compiler.errors.size(), t + "C3");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "C3");
        Assert::equals("End of file while parsing String.", compiler.errors[0]->message, t + "C4");

        //non existent escape character
        compiler.clearErrors();

        stream = std::stringstream("\"this escaped character does NOT exist: \\y \"");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "D2");
        checkLocation(&loc, 1, 1, 1, 43, t + "D2_loc"); //43 is the location that the error happened
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "D3");
        Assert::equals("Illegal escaped character inside String.", compiler.errors[0]->message, t + "D4");

        //EOF during escaped character
        compiler.clearErrors();

        stream = std::stringstream("\" EOF during weird situation: \\");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ERROR, t + "E2");
        checkLocation(&loc, 1, 1, 1, 33, t + "E2_loc");
        Assert::equals(1, compiler.errors.size(), t + "E3");
        Assert::equals(EulErrorType::LEXER, compiler.errors[0]->type, t + "E3");
        Assert::equals("Illegal escaped character inside String.", compiler.errors[0]->message, t + "E4");
    }
    //endregion




    //region OPERATORS
    private: static void parseOperatorsTest(const std::string& t) {
        Compiler compiler(0);
        EulParsingContext ctx(&compiler, 0);
        yy::EulParser::location_type loc;


        //test + - families, and () pair
        std::stringstream stream = std::stringstream("1+1-(2++) +=\n--5-=+");
        EulScanner scanner(&stream);
        checkIntToken(scanner, &ctx, &loc, 1, 4, 0, t + "A1");
        checkLocation(&loc, 1, 1, 1, 2, t + "A1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "A2");
        checkLocation(&loc, 1, 2, 1, 3, t + "A2_loc");
        checkIntToken(scanner, &ctx, &loc, 1, 4, 0, t + "A3");
        checkLocation(&loc, 1, 3, 1, 4, t + "A3_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::MINUS, t + "A4");
        checkLocation(&loc, 1, 4, 1, 5, t + "A4_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PARENTHESIS_OPEN, t + "A5");
        checkLocation(&loc, 1, 5, 1, 6, t + "A5_loc");
        checkIntToken(scanner, &ctx, &loc, 2, 4, 0, t + "A6");
        checkLocation(&loc, 1, 6, 1, 7, t + "A6_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::INCREASE, t + "A7");
        checkLocation(&loc, 1, 7, 1, 9, t + "A7_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PARENTHESIS_CLOSE, t + "A8");
        checkLocation(&loc, 1, 9, 1, 10, t + "A8_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN_PLUS, t + "A9");
        checkLocation(&loc, 1, 11, 1, 13, t + "A9_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "A10");
        checkLocation(&loc, 1, 13, 2, 1, t + "A10_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::DECREASE, t + "A11");
        checkLocation(&loc, 2, 1, 2, 3, t + "A11_loc");
        checkIntToken(scanner, &ctx, &loc, 5, 4, 0, t + "A12");
        checkLocation(&loc, 2, 3, 2, 4, t + "A12_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN_MINUS, t + "A13");
        checkLocation(&loc, 2, 4, 2, 6, t + "A13_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PLUS, t + "A14");
        checkLocation(&loc, 2, 6, 2, 7, t + "A14_loc");

        //test *  / and % families and [] pair
        stream = std::stringstream("1%1*[2*=] /=\n5%=/4");
        scanner.switch_streams(&stream);
        loc.initialize();
        checkIntToken(scanner, &ctx, &loc, 1, 4, 0, t + "B1");
        checkLocation(&loc, 1, 1, 1, 2, t + "B1_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::PERCENT, t + "B2");
        checkLocation(&loc, 1, 2, 1, 3, t + "B2_loc");
        checkIntToken(scanner, &ctx, &loc, 1, 4, 0, t + "B3");
        checkLocation(&loc, 1, 3, 1, 4, t + "B3_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::STAR, t + "B4");
        checkLocation(&loc, 1, 4, 1, 5, t + "B4_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::SQUARE_OPEN, t + "B5");
        checkLocation(&loc, 1, 5, 1, 6, t + "B5_loc");
        checkIntToken(scanner, &ctx, &loc, 2, 4, 0, t + "B6");
        checkLocation(&loc, 1, 6, 1, 7, t + "B6_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN_STAR, t + "B7");
        checkLocation(&loc, 1, 7, 1, 9, t + "B7_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::SQUARE_CLOSE, t + "B8");
        checkLocation(&loc, 1, 9, 1, 10, t + "B8_loc");
        checkTokenType(scanner,&ctx, &loc, yy::EulParser::token::ASSIGN_DIV, t + "B9");
        checkLocation(&loc, 1, 11, 1, 13, t + "B9_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::NL, t + "B10");
        checkLocation(&loc, 1, 13, 2, 1, t + "B10_loc");
        checkIntToken(scanner, &ctx, &loc, 5, 4, 0, t + "B11");
        checkLocation(&loc, 2, 1, 2, 2, t + "B11_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::ASSIGN_MOD, t + "B12");
        checkLocation(&loc, 2, 2, 2, 4, t + "B12_loc");
        checkTokenType(scanner, &ctx, &loc, yy::EulParser::token::SLASH, t + "B13");
        checkLocation(&loc, 2, 4, 2, 5, t + "B13_loc");
        checkIntToken(scanner, &ctx, &loc, 4, 4, 0, t + "B14");
        checkLocation(&loc, 2, 5, 2, 6, t + "B14_loc");
    }
    //endregion


    public: static void runAll() {
        multiLineCommentTest("EulScannerTest.multiLineCommentTest ");
        singleLineCommentTest("EulScannerTest.singleLineCommentTest ");
        parseIntegerTest("EulScannerTest.parseIntegerTest ");
        parseFloatTest("EulScannerTest.parseFloatTest ");
        parseIdTest("EulScannerTest.parseIdTest ");
        parseCharTest("EulScannerTest.parseCharTest ");
        parseStringTest("EulScannerTest.parseStringTest ");
        parseOperatorsTest("EulScannerTest.parseOperatorsTest ");
    }

};