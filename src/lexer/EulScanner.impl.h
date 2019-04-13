#pragma once


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




//region LOCATION UTILS
void EulScanner::advanceLine(yy::EulParser::location_type* loc) {
    loc->end.lines();
    loc->end.column = 1;
}
//endregion



//region SKIPPING
void EulScanner::skipMultiLineComment(Compiler* compiler, yy::EulParser::location_type* loc) {
  int c;

  while (1) {
    //advance the cursor
    c = this->yyinput();
    //check special cases
    switch(c) {
      case '*':
        loc->columns();

        //eat possible repeating *
        while ( (c = this->yyinput()) == '*' ) loc->columns();
        loc->columns();

        if ( c == '/' )  return;
        else if (c=='\n') EulScanner::advanceLine(loc);
        break;

      case '\n':
        EulScanner::advanceLine(loc);
        break;

      case YY_NULL:
        compiler->addError(EulErrorType::LEXER, "End of file while parsing comment");
        return;

      default: loc->columns();
    }
  }
}


void EulScanner::skipSingleLineComment(yy::EulParser::location_type* loc) {
    int c;

    while (1) {
        c = this->yyinput(); //we will stop in only 2 cases: \n and EOF. In any of these, we will reset yytext.
        switch(c) {
            case '\n':
            case YY_NULL:
                EulScanner::advanceLine(loc);
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
std::shared_ptr<EulStringNode> EulScanner::parseStringValue(Compiler* compiler, yy::EulParser::location_type* loc) {
    int c;
    std::string& buffer = compiler->buffer;
    buffer.clear();

    while (1) {
        switch(c = this->yyinput()) {
            case '"': {
                loc->columns();
                return std::make_shared<EulStringNode>(buffer);
            }

            //case '$':
                //Compiler_pushToken(EulTokenType_INTERPOLATED_VARIABLE_STRING);
                //return EulTokenType_INTERPOLATED_VARIABLE_STRING;

            case '\n': {
                buffer += '\n';
                EulScanner::advanceLine(loc);
                continue;
            }

            case '\\': {
                loc->columns();

                int c2 = this->yyinput();
                loc->columns();
                short int escaped = LexerUtils_toEscapedStringChar(c2);

                //check if it failed
                if (escaped==-1) {
                    compiler->addError(EulErrorType::LEXER, "Illegal escaped character inside String.");
                    return 0;
                }

                //add the caracter to the buffer
                buffer +=  (char)escaped;
                break;
            }

            case YY_NULL: {
                compiler->addError(EulErrorType::LEXER, "End of file while parsing String.");
                return 0;
            }

            default:
                loc->columns();
                buffer +=  c;
        }
    }

    return 0;
}

std::shared_ptr<EulCharNode> EulScanner::parseEscapedChar(Compiler* compiler, yy::EulParser::location_type* loc) {
    int c = this->yyinput();
    loc->columns();


    const short int escaped = LexerUtils_toEscapedChar(c);

    //check for failure.
    if (escaped==-1) {
        compiler->addError(EulErrorType::LEXER, "Illegal escaped character.");
        return 0;
    }

    //read closing ' and return error if it is not found.
    c = this->yyinput();
    if (c != '\'') {
        compiler->addError(EulErrorType::LEXER, "Closing ' expected in char literal.");
        return 0;
    }
    loc->columns();

    return std::make_shared<EulCharNode>(escaped, 8);
}
//endregion
