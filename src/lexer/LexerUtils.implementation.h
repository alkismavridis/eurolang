//region UTIL FUNCTIONS
/**
		Returns the escaped character that can be found inside a string.
		It must be called after backslash is read.
		Returns the escaped character, or -1 in case of error.
*/
short int LexerUtils_toEscapedStringChar(int c) {
  switch(c) {
		case 'n': return '\n';
		case 't': return '\t';
		case 'r': return '\r';
		case 'f': return '\f';
		case '\\': return '\\';
		case 'b': return '\b';
		case '0': return '\0';
		default: return -1;
	}
}

/**
		Returns the escaped character that can be found inside a char literal.
		It must be called after backslash is read.
		Returns the escaped character, or -1 in case of error.
*/
short int LexerUtils_toEscapedChar(int c) {
  switch(c) {
		case 'n': return '\n';
		case 't': return '\t';
		case 'r': return '\r';
		case 'f': return '\f';
		case '\\': return '\\';
		case 'b': return '\b';
		case '0': return '\0';
		default: return -1;
	}
}
//endregion




//region SKIPPING
void LexerUtils_skipMultiLineComment(Compiler* compiler) {
  void* scanner = compiler->scanner;
  register int c;

  while (1) {
    //andvance the cursor
    c = input(scanner);

    //check special cases
    switch(c) {
      case '*':
        while ( (c = input(scanner)) == '*' ) ;            //eat repeating *
        if ( c == '/' ) return;    /* found the end return a "to be ignored" token*/
        else if (c=='\n') ; //yylineno is automatically set
        break;

      case '\n':
        //yylineno is automatically set
        break;

      case YY_NULL:
        Compiler_makeLexerError(compiler, "End of file while parsing comment");
        return;
    }
  }
}


void LexerUtils_skipSingleLineComment(Compiler* compiler) {
  register int c;
  void* scanner = compiler->scanner;


	while (1) {
		c = input(scanner); //we will stop in only 2 cases: \n and EOF. In any of these, we will reset yytext.
    switch(c) {
      case '\n':
      case YY_NULL:
        return;
    }
	}
}
//endregion




//region PARSING
/**
  Parses and returns a string token.
  String token creation need a buffer.

  For ensuring best possible reusability, we will store this buffer at the Compiler object.
*/
EulToken* LexerUtils_parseStringValue(Compiler* compiler) {
  EulToken* ret = malloc(sizeof(EulToken));
  ret->type = EulTokenType_STRING;
  void* scanner = compiler->scanner;

  register int c;
	compiler->stringBufferIndex = 0; //reset the buffer index

  loop:
  while (1) {
  	switch(c = input(scanner)) {
  		case '"':
				Compiler_addToStringBuffer(compiler, '\0'); //terminate the string
				ret->value.asString = malloc(compiler->stringBufferIndex); //make space for the string in token
				strcpy(ret->value.asString, compiler->stringBuffer);	//copy the string
				return ret;

  		//case '$':
  			//Compiler_pushToken(EulTokenType_INTERPOLATED_VARIABLE_STRING);
  			//return EulTokenType_INTERPOLATED_VARIABLE_STRING;

  		case '\n': {
				Compiler_addToStringBuffer(compiler, '\n');
  			continue; //loop
  		}

  		case '\\': {
				int c2 = input(scanner);
  			short int escaped = LexerUtils_toEscapedStringChar(c2);

				//check if it failed
  			if (escaped==-1) {
          Compiler_makeLexerError(compiler, "Illegal escaped character inside String.");
          free(ret);
					return NULL;
				}

				//add the caracter to the buffer
				Compiler_addToStringBuffer(compiler, (char)escaped);
				break;
  		}

      case YY_NULL: {
        Compiler_makeLexerError(compiler, "End of file while parsing String.");
        free(ret);
        return NULL;
      }

			default:
				Compiler_addToStringBuffer(compiler, c);
  	}
  }

  return ret;
}

EulToken* LexerUtils_parseEscapedChar(Compiler* compiler) {
  EulToken* ret = malloc(sizeof(EulToken));
  ret->type = EulTokenType_CHAR;

  int c = input(compiler->scanner);
	const short int escaped = LexerUtils_toEscapedChar(c);

	//check for failure.
	if (escaped==-1) {
		Compiler_makeLexerError(compiler, "Illegal escaped character.");
    free(ret);
		return NULL;
	}

	//read closing ' and return error if it is not found.
	c = input(compiler->scanner);
	if (c != '\'') {
		Compiler_makeLexerError(compiler, "Closing ' expected in char literal.");
    free(ret);
		return NULL;
	}

	//setup the token and return.
	ret->value.asInt.value = escaped;
	ret->value.asInt.size = 1;		//all escaped characters are 1 byte long
	return ret;
}
//endregion
