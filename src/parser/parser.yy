%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parser_class_name {EulParser}


%code requires
{
    class EulScanner;


    # include <string>
    # include <map>
    # include <forward_list>

    #include "../core/EulToken/EulTokenType.h"
    #include "../core/EulToken/EulToken.h"
    #include "../core/EulToken/EulIntToken.h"
    #include "../core/EulToken/EulFloatToken.h"
    #include "../core/EulToken/EulCharToken.h"
    #include "../core/EulToken/EulStringToken.h"
    #include "../core/EulToken/EulIdToken.h"
    #include "../core/EulAst/EulAstType.h"
    #include "../core/EulAst/EulAst.h"
    #include "../core/EulAst/EulSymbol.h"
    #include "../core/EulAst/EulStatement/EulStatementType.h"
    #include "../core/EulAst/EulStatement/EulStatement.h"
    #include "../core/EulAst/EulStatement/EulImportStatement.h"
    #include "../core/EulAst/EulStatement/EulExportStatement.h"

    #include "../core/EulSourceFile/EulSourceFile.h"
    #include "../core/EulProgram/EulProgram.h"
    #include "../core/Compiler/Compiler.h"



    # ifndef YY_NULLPTR
    #  if defined __cplusplus && 201103L <= __cplusplus
    #   define YY_NULLPTR nullptr
    #  else
    #   define YY_NULLPTR 0
    #  endif
    # endif
}





// The parsing context.
%parse-param { EulScanner &scanner }
%parse-param { Compiler  *compiler  }
%lex-param   { Compiler *compiler }


%code {
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "../lexer/EulScanner.h"


    /* include for all compiler functions */

    #undef yylex
    #define yylex scanner.yylex
}

%define api.value.type variant
// %define parse.assert



%token
    END  0  "end of file"
    IF
    FOR
    WHILE
    VAR
    CONST
    VAL

    PLUS
    MINUS
    TILDE
    NOT
    NOT_EQUALS
    NOT_SAME
    AT
    HASH
    DOLLAR
    PERCENT
    ASSIGN_MOD
    XOR
    ASSIGN_XOR
    BIN_AND
    AND
    ASSIGN_AND
    STAR
    ASSIGN_STAR
    PARENTHESIS_OPEN
    PARENTHESIS_CLOSE
    DECREASE
    ASSIGN_MINUS
    ARROW
    ASSIGN
    EQUALS
    SAME
    INCREASE
    ASSIGN_PLUS
    SQUARE_OPEN
    SQUARE_CLOSE
    CURLY_OPEN
    CURLY_CLOSE
    BACKSLASH
    BIN_OR
    OR
    ASSIGN_OR
    SEMICOLON
    COLON
    SLASH
    ASSIGN_DIV
    QUESTION
    DOT
    COMMA
    LESS
    LESS_EQUALS
    LSHIFT
    ASSIGN_LSHIFT
    MORE
    MORE_EQUALS
    RSHIFT
    ASSIGN_RSHIFT
    NL
    ERROR
;


%token
    <EulIntToken*> INT
    <EulFloatToken*> FLOAT
    <EulStringToken*> STRING
    <EulCharToken*> CHAR
    <EulIdToken*> ID
;

%destructor { std::cout << "I destruct!!" << std::endl; } <*>



%token <std::string> IDENTIFIER "identifier"


%locations


%printer { yyoutput << $$; } <*>;


%%
list_option : END | list END;

list
  : item
  | list item
  ;

item
  : IF   { std::cout << "IF\n"; }
  ;

%%


void yy::EulParser::error( const location_type &l, const std::string &err_message ) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}