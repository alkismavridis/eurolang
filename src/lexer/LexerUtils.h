//region SKIPPING
void LexerUtils_skipMultiLineComment(Compiler* compiler);
void LexerUtils_skipSingleLineComment(Compiler* compiler);
//endregion




//region PARSING
EulToken* LexerUtils_parseStringValue(Compiler* compiler);
EulToken* LexerUtils_parseEscapedChar(Compiler* compiler);
//endregion
