#pragma once



//region UTIL FUNCTIONS
void VocabularyTest_startParsingString(Compiler *compiler, char *source) {
	yyrestart( fmemopen (source, strlen (source), "r"), compiler->scanner );
	yyset_lineno(1, compiler->scanner);
}

void VocabularyTest_checkIntToken(Compiler *compiler, unsigned long exected, unsigned char size, char isUnsigned, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(EulTokenType_INT, type, majorMessage, minorMessage);
	assertIntEquals(exected, tok->value.asInt.value, majorMessage, minorMessage);
	assertIntEquals(size, tok->value.asInt.size, majorMessage, minorMessage);
	assertIntEquals(isUnsigned, tok->value.asInt.isUnsigned, majorMessage, minorMessage);
	assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);
	EulToken_deinit(tok);
}

void VocabularyTest_checkFloatToken(Compiler *compiler, double exected, unsigned char size, double tolerance, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(EulTokenType_FLOAT, type, majorMessage, minorMessage);
	assertDoubleEquals(exected, tok->value.asFloat.value, tolerance, majorMessage, minorMessage);
	assertIntEquals(size, tok->value.asFloat.size, majorMessage, minorMessage);
	assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);
	EulToken_deinit(tok);
}

void VocabularyTest_checkCharToken(Compiler *compiler, unsigned long int exected, unsigned char size, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(EulTokenType_CHAR, type, majorMessage, minorMessage);
	assertIntEquals(exected, tok->value.asInt.value, majorMessage, minorMessage);
	assertIntEquals(size, tok->value.asInt.size, majorMessage, minorMessage);
	assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);
	EulToken_deinit(tok);
}

void VocabularyTest_checkStringToken(Compiler *compiler, char* expected, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(EulTokenType_STRING, type, majorMessage, minorMessage);
	assertStringEquals(expected, tok->value.asString, majorMessage, minorMessage);
	assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);
	EulToken_deinit(tok);
}

/* If line:0 is passed, no check on line will be made*/
void VocabularyTest_checkTokenType(Compiler *compiler, int expected, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(expected, type, majorMessage, minorMessage);
	if (line>0) assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);
	if (tok != 0) EulToken_deinit(tok);
}

void VocabularyTest_checkIdToken(Compiler *compiler, char* name, unsigned int line, char* majorMessage, char* minorMessage) {
	EulToken* tok;
	int type = yylex(&tok, compiler->scanner, compiler);

	assertIntEquals(EulTokenType_ID, type, majorMessage, minorMessage);
	assertStringEquals(name, tok->value.asId, majorMessage, minorMessage);
	assertIntEquals(line, yyget_lineno(compiler->scanner), majorMessage, minorMessage);

	//cleanup EulToken
	EulToken_deinit(tok);
}
//endregion


void VocabularyTest_multiLineCommentTest(char* t) {
	Compiler compiler;
	FILE* myFile;
	Compiler_init(&compiler, "", ({FILE* __fn__(char* ch){ return myFile; } __fn__; }), 0);
	//Compiler_init(&compiler, 0);

	VocabularyTest_startParsingString( &compiler, "123/*hello\n*1/2*3*/world" );
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "A1");
	VocabularyTest_checkIdToken(&compiler, "world", 2, t, "A2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_EOF, 0, t, "A3");


	//start at the end of the line. Change line during ***
	VocabularyTest_startParsingString( &compiler, "123/*\n*1/2***\n3*/abc\n12" );
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "B1");
	VocabularyTest_checkIdToken(&compiler, "abc", 3, t, "B2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 4, t, "B3");
	VocabularyTest_checkIntToken(&compiler, 12, 4, 0, 4, t, "B4");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_EOF, 0, t, "B5");

	//no content
	VocabularyTest_startParsingString( &compiler, ";/**/world12" );
	VocabularyTest_checkTokenType(&compiler, EulTokenType_SEMICOLON, 1, t, "C1");
	VocabularyTest_checkIdToken(&compiler, "world12", 1, t, "C2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_EOF, 0, t, "C3");

	//end of file while parsing. This must generate an appropriate error.
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "D1");

	VocabularyTest_startParsingString( &compiler, "123/*\nabcdefgh\n12"	 );
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "D2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "D3");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "D4");
	assertStringEquals("End of file while parsing comment", compiler.errorMessage, t, "D5");
	Compiler_deinit(&compiler);
}

/*void VocabularyTest_singleLineCommentTest(char* t) {
	Compiler compiler;
 	Compiler_init(&compiler, 0);

	//skip comments
	VocabularyTest_startParsingString( &compiler, "123//comment1\nend++" );
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "A1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 2, t, "A2");
	VocabularyTest_checkIdToken(&compiler, "end", 2, t, "A3");

	//meet EOF during single line token. This should be allowed and just return the EOF.
	VocabularyTest_startParsingString( &compiler, "123//comment1" );
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "B1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 0, t, "B2");
	Compiler_deinit(&compiler);
}


void VocabularyTest_parseIntegerTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);

	//end at EOF
	VocabularyTest_startParsingString( &compiler, "1");
	VocabularyTest_checkIntToken(&compiler, 1, 4, 0, 1, t, "A1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_EOF, 0, t, "A2");

	//end at space
	VocabularyTest_startParsingString( &compiler, "123 ");
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "B1");

	//end at operator
	VocabularyTest_startParsingString( &compiler, "123=");
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "C1");

	//end at letter other that casting
	VocabularyTest_startParsingString( &compiler, "123p");
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "D1");


	//cast size
	VocabularyTest_startParsingString(&compiler, "123s8");
	VocabularyTest_checkIntToken(&compiler, 123, 8, 0, 1, t, "E1");


	//unsigned literal, stop at operator, and then at space
	VocabularyTest_startParsingString(&compiler, "5u123+52u2 ");
	VocabularyTest_checkIntToken(&compiler, 5, 123, 1, 1, t, "F1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "F2");
	VocabularyTest_checkIntToken(&compiler, 52, 2, 1, 1, t, "F3");

	//default sizes. Stop at operator, at space, at letter, at EOF
	VocabularyTest_startParsingString(&compiler, "5u+52s 5sa 5u");
	VocabularyTest_checkIntToken(&compiler, 5, 4, 1, 1, t, "G1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "G2");
	VocabularyTest_checkIntToken(&compiler, 52, 4, 0, 1, t, "G3");
	VocabularyTest_checkIntToken(&compiler, 5, 4, 0, 1, t, "G4");
	VocabularyTest_checkIdToken(&compiler, "a", 1, t, "G5");
	VocabularyTest_checkIntToken(&compiler, 5, 4, 1, 1, t, "G6");

	//test zero starting
	VocabularyTest_startParsingString(&compiler, "0 0u 0s 0u123 0s123 0+0u12+0s");
	VocabularyTest_checkIntToken(&compiler, 0, 4, 0, 1, t, "H1");
	VocabularyTest_checkIntToken(&compiler, 0, 4, 1, 1, t, "H2");
	VocabularyTest_checkIntToken(&compiler, 0, 4, 0, 1, t, "H3");
	VocabularyTest_checkIntToken(&compiler, 0, 123, 1, 1, t, "H4");
	VocabularyTest_checkIntToken(&compiler, 0, 123, 0, 1, t, "H5");
	VocabularyTest_checkIntToken(&compiler, 0, 4, 0, 1, t, "H6");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "H7");
	VocabularyTest_checkIntToken(&compiler, 0, 12, 1, 1, t, "H8");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "H9");
	VocabularyTest_checkIntToken(&compiler, 0, 4, 0, 1, t, "H10");
	Compiler_deinit(&compiler);
}


void VocabularyTest_parseFloatTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);


	//int and float part present
	VocabularyTest_startParsingString(&compiler, "0.0+1.0 123.456hello 1.2");
	VocabularyTest_checkFloatToken(&compiler, 0.0, 8, 0.00000001, 1, t, "A1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "A2");
	VocabularyTest_checkFloatToken(&compiler, 1.0, 8, 0.00000001, 1, t, "A3");
	VocabularyTest_checkFloatToken(&compiler, 123.456, 8, 0.00000001, 1, t, "A4");
	VocabularyTest_checkIdToken(&compiler, "hello", 1, t, "A5");
	VocabularyTest_checkFloatToken(&compiler, 1.2, 8, 0.00000001, 1, t, "A6");

	//int part missing, or float part missing
	VocabularyTest_startParsingString(&compiler, "0. 123.+.123 1.hello 2.");
	VocabularyTest_checkFloatToken(&compiler, 0.0, 8, 0.00000001, 1, t, "B1");
	VocabularyTest_checkFloatToken(&compiler, 123.0, 8, 0.00000001, 1, t, "B2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "B3");
	VocabularyTest_checkFloatToken(&compiler, 0.123, 8, 0.00000001, 1, t, "B4");
	VocabularyTest_checkFloatToken(&compiler, 1.0, 8, 0.00000001, 1, t, "B5");
	VocabularyTest_checkIdToken(&compiler, "hello", 1, t, "B6");
	VocabularyTest_checkFloatToken(&compiler, 2.0, 8, 0.00000001, 1, t, "B7");


	//casting with size
	VocabularyTest_startParsingString(&compiler, "0f7 1f32+1.f4 .4f12 = 3.3f12");
	VocabularyTest_checkFloatToken(&compiler, 0, 7, 0.00000001, 1, t, "C1");
	VocabularyTest_checkFloatToken(&compiler, 1, 32, 0.00000001, 1, t, "C2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "C3");
	VocabularyTest_checkFloatToken(&compiler, 1, 4, 0.00000001, 1, t, "C4");
	VocabularyTest_checkFloatToken(&compiler, 0.4, 12, 0.00000001, 1, t, "C5");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN, 1, t, "C6");
	VocabularyTest_checkFloatToken(&compiler, 3.3, 12, 0.00000001, 1, t, "C7");

	//casting default size
	VocabularyTest_startParsingString(&compiler, "0f 1f+1.f .4f = 3.3f");
	VocabularyTest_checkFloatToken(&compiler, 0, 8, 0.00000001, 1, t, "C1");
	VocabularyTest_checkFloatToken(&compiler, 1, 8, 0.00000001, 1, t, "C2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "C3");
	VocabularyTest_checkFloatToken(&compiler, 1.0, 8, 0.00000001, 1, t, "C4");
	VocabularyTest_checkFloatToken(&compiler, 0.4, 8, 0.00000001, 1, t, "C5");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN, 1, t, "C6");
	VocabularyTest_checkFloatToken(&compiler, 3.3, 8, 0.00000001, 1, t, "C7");
	Compiler_deinit(&compiler);
}

void VocabularyTest_parseWordTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);


	//int and float part present
	VocabularyTest_startParsingString(&compiler, "hello123__ par123+hello_");
	VocabularyTest_checkIdToken(&compiler, "hello123__", 1, t, "A1");
	VocabularyTest_checkIdToken(&compiler, "par123", 1, t, "A2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "A3");
	VocabularyTest_checkIdToken(&compiler, "hello_", 1, t, "A4");
	Compiler_deinit(&compiler);
}

void VocabularyTest_parseCharTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);

	//1 byte long unicodes
	VocabularyTest_startParsingString(&compiler, "'b' 'n'+'''");
	VocabularyTest_checkCharToken(&compiler, 'b', 1, 1, t, "A1");
	VocabularyTest_checkCharToken(&compiler, 'n', 1, 1, t, "A2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "A3");
	VocabularyTest_checkCharToken(&compiler, '\'', 1, 1, t, "A4");

	//2 byte long unicodes
	VocabularyTest_startParsingString(&compiler, "'ώ' 'ϋ' 'π' 'ü'");
	VocabularyTest_checkCharToken(&compiler, 'ώ', 2, 1, t, "B1");
	VocabularyTest_checkCharToken(&compiler, 'ϋ', 2, 1, t, "B2");
	VocabularyTest_checkCharToken(&compiler, 'π', 2, 1, t, "B3");
	VocabularyTest_checkCharToken(&compiler, 'ü', 2, 1, t, "B4");

	//4 byte long unicodes
	VocabularyTest_startParsingString(&compiler, "'𠜎' '𡇙' '😌' '🙋'");
	VocabularyTest_checkCharToken(&compiler, '𠜎', 4, 1, t, "C1");
	VocabularyTest_checkCharToken(&compiler, '𡇙', 4, 1, t, "C2");
	VocabularyTest_checkCharToken(&compiler, '😌', 4, 1, t, "C3");
	VocabularyTest_checkCharToken(&compiler, '🙋', 4, 1, t, "C4");

	//parse escaped chars
	VocabularyTest_startParsingString(&compiler, "'\\n' '\\t' '\\r' '\\f' '\\\\' '\\b' '\\0'");
	VocabularyTest_checkCharToken(&compiler, '\n', 1, 1, t, "D1");
	VocabularyTest_checkCharToken(&compiler, '\t', 1, 1, t, "D2");
	VocabularyTest_checkCharToken(&compiler, '\r', 1, 1, t, "D3");
	VocabularyTest_checkCharToken(&compiler, '\f', 1, 1, t, "D4");
	VocabularyTest_checkCharToken(&compiler, '\\', 1, 1, t, "D5");
	VocabularyTest_checkCharToken(&compiler, '\b', 1, 1, t, "D6");
	VocabularyTest_checkCharToken(&compiler, '\0', 1, 1, t, "D7");



	//test failed escaped sequenses
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "E1");
	VocabularyTest_startParsingString(&compiler, "'\\w'");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "E2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "E3");
	assertStringEquals("Illegal escaped character.", compiler.errorMessage, t, "E4");


	//EOF during escaped character
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "F1");
	VocabularyTest_startParsingString(&compiler, "'\\");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "F2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "F3");
	assertStringEquals("Illegal escaped character.", compiler.errorMessage, t, "F4");


	//To many characters after escaped sequence error
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "G1");
	VocabularyTest_startParsingString(&compiler, "'\\nnn'");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "G2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "G3");
	assertStringEquals("Closing ' expected in char literal.", compiler.errorMessage, t, "G4");
	Compiler_deinit(&compiler);
}

void VocabularyTest_parseStringTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);


	//read simple String and multi line string
	VocabularyTest_startParsingString(&compiler, "\"hello world\"123\n\"multi\nline\n\nstring\"end");
	VocabularyTest_checkStringToken(&compiler, "hello world", 1, t, "A1");
	VocabularyTest_checkIntToken(&compiler, 123, 4, 0, 1, t, "A2");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 2, t, "A3");
	VocabularyTest_checkStringToken(&compiler, "multi\nline\n\nstring", 5, t, "A4");
	VocabularyTest_checkIdToken(&compiler, "end", 5, t, "A5");

	//test escaped characters
	VocabularyTest_startParsingString(&compiler, "\"start escaped\\n123\\tabc\\rhello\\fworld\n\\\\backslashes\\bxyz\"end");
	VocabularyTest_checkStringToken(&compiler, "start escaped\n123\tabc\rhello\fworld\n\\backslashes\bxyz", 2, t, "B1");
	VocabularyTest_checkIdToken(&compiler, "end", 2, t, "B2");

	//EOF during string parsing
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "C1");
	VocabularyTest_startParsingString(&compiler, "\" End of file will be found before string is closed.");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "C2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "C3");
	assertStringEquals("End of file while parsing String.", compiler.errorMessage, t, "C4");

	//non existent escape character
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "D1");
	VocabularyTest_startParsingString(&compiler, "\"this escaped character does NOT exist: \\y \"");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "D2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "D3");
	assertStringEquals("Illegal escaped character inside String.", compiler.errorMessage, t, "D4");

	//EOF during escaped character
	Compiler_clearError(&compiler);
	assertIntEquals(ErrorType_NO_ERROR, compiler.errorCode, t, "E1");
	VocabularyTest_startParsingString(&compiler, "\" EOF during weird situation: \\");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ERROR, 0, t, "E2");
	assertIntEquals(ErrorType_LEXER, compiler.errorCode, t, "E3");
	assertStringEquals("Illegal escaped character inside String.", compiler.errorMessage, t, "E4");
	Compiler_deinit(&compiler);
}

void VocabularyTest_operatorTest(char* t) {
	Compiler compiler;
	Compiler_init(&compiler, 0);


	//test + - families, and () pair
	VocabularyTest_startParsingString(&compiler, "1+1-(2++) +=\n--5-=+");
	VocabularyTest_checkIntToken(&compiler, 1, 4, 0, 1, t, "A1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 1, t, "A2");
	VocabularyTest_checkIntToken(&compiler, 1, 4, 0, 1, t, "A3");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_MINUS, 1, t, "A4");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PARENTHESIS_OPEN, 1, t, "A5");
	VocabularyTest_checkIntToken(&compiler, 2, 4, 0, 1, t, "A6");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_INCREASE, 1, t, "A7");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PARENTHESIS_CLOSE, 1, t, "A8");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN_PLUS, 1, t, "A9");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 2, t, "A9");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_DECREASE, 2, t, "A10");
	VocabularyTest_checkIntToken(&compiler, 5, 4, 0, 2, t, "A11");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN_MINUS, 2, t, "A12");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PLUS, 2, t, "A13");

	//test *  / and % families and [] pair
	VocabularyTest_startParsingString(&compiler, "1%1*[2*=] /=\n5%=/4");
	VocabularyTest_checkIntToken(&compiler, 1, 4, 0, 1, t, "B1");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_PERCENT, 1, t, "B2");
	VocabularyTest_checkIntToken(&compiler, 1, 4, 0, 1, t, "B3");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_STAR, 1, t, "B4");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_SQUARE_OPEN, 1, t, "B5");
	VocabularyTest_checkIntToken(&compiler, 2, 4, 0, 1, t, "B6");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN_STAR, 1, t, "B7");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_SQUARE_CLOSE, 1, t, "B8");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN_DIV, 1, t, "B9");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_NL, 2, t, "B10");
	VocabularyTest_checkIntToken(&compiler, 5, 4, 0, 2, t, "B11");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_ASSIGN_MOD, 2, t, "B12");
	VocabularyTest_checkTokenType(&compiler, EulTokenType_SLASH, 2, t, "B13");
	VocabularyTest_checkIntToken(&compiler, 4, 4, 0, 2, t, "B14");
	Compiler_deinit(&compiler);
}*/

void VocabularyTest_runAllTests() {
	//VocabularyTest_multiLineCommentTest("VocabularyTest_multiLineCommentTest");
	/*VocabularyTest_singleLineCommentTest("VocabularyTest_singleLineCommentTest");
	VocabularyTest_parseIntegerTest("VocabularyTest_parseIntegerTest"); //TODO hex and octals, e support
	VocabularyTest_parseFloatTest("VocabularyTest_parseFloatTest");			//TODO e support
	VocabularyTest_parseWordTest("VocabularyTest_parseWordTest");
	VocabularyTest_parseCharTest("VocabularyTest_parseCharTest");				//TODO sizes, \u ??
	VocabularyTest_parseStringTest("VocabularyTest_parseStringTest");		//TODO interpolation
	VocabularyTest_operatorTest("VocabularyTest_operatorTest");					//TODO include all operators in unit tests */
}
