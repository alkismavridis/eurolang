%output  "../src/parser/autoGenerated.EulSyntax.c"
%defines "../src/parser/autoGenerated.EulSyntax.h"
%define api.pure full
%lex-param   { void* scanner }
%lex-param   { Compiler *compiler }
%parse-param { yyscan_t scanner }
%parse-param { Compiler *compiler }

%code requires {
  #include <stdio.h>
  #include "../constants/Constants.h"
  #include "../core/EulNodeList/EulNodeList.h"
  #include "../core/EulSourceFile/EulSourceFile.h"
  #include "../core/EulProgram/EulProgram.h"
  #include "../core/Compiler/Compiler.h"
  #include "../core/EulToken/EulToken.h"

  #define YYSTYPE EulToken*
  #define YYDEBUG 1

  #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void* yyscan_t;
  #endif


  int yylex();
  int yyerror();
}

//region terminals
  %token EulTokenType_INT
  %token EulTokenType_FLOAT
  %token EulTokenType_STRING
  %token EulTokenType_CHAR
  %token EulTokenType_ID

  %token EulTokenType_IF
  %token EulTokenType_FOR
  %token EulTokenType_WHILE
  %token EulTokenType_VAR
  %token EulTokenType_CONST
  %token EulTokenType_VAL

  %token EulTokenType_PLUS
  %token EulTokenType_MINUS
  %token EulTokenType_TILDE
  %token EulTokenType_NOT
  %token EulTokenType_NOT_EQUALS
  %token EulTokenType_NOT_SAME
  %token EulTokenType_AT
  %token EulTokenType_HASH
  %token EulTokenType_DOLLAR
  %token EulTokenType_PERCENT
  %token EulTokenType_ASSIGN_MOD
  %token EulTokenType_XOR
  %token EulTokenType_ASSIGN_XOR
  %token EulTokenType_BIN_AND
  %token EulTokenType_AND
  %token EulTokenType_ASSIGN_AND
  %token EulTokenType_STAR
  %token EulTokenType_ASSIGN_STAR
  %token EulTokenType_PARENTHESIS_OPEN
  %token EulTokenType_PARENTHESIS_CLOSE
  %token EulTokenType_DECREASE
  %token EulTokenType_ASSIGN_MINUS
  %token EulTokenType_ARROW
  %token EulTokenType_ASSIGN
  %token EulTokenType_EQUALS
  %token EulTokenType_SAME
  %token EulTokenType_INCREASE
  %token EulTokenType_ASSIGN_PLUS
  %token EulTokenType_SQUARE_OPEN
  %token EulTokenType_SQUARE_CLOSE
  %token EulTokenType_CURLY_OPEN
  %token EulTokenType_CURLY_CLOSE
  %token EulTokenType_BACKSLASH
  %token EulTokenType_BIN_OR
  %token EulTokenType_OR
  %token EulTokenType_ASSIGN_OR
  %token EulTokenType_SEMICOLON
  %token EulTokenType_COLON
  %token EulTokenType_SLASH
  %token EulTokenType_ASSIGN_DIV
  %token EulTokenType_QUESTION
  %token EulTokenType_DOT
  %token EulTokenType_COMMA
  %token EulTokenType_LESS
  %token EulTokenType_LESS_EQUALS
  %token EulTokenType_LSHIFT
  %token EulTokenType_ASSIGN_LSHIFT
  %token EulTokenType_MORE
  %token EulTokenType_MORE_EQUALS
  %token EulTokenType_RSHIFT
  %token EulTokenType_ASSIGN_RSHIFT
  %token EulTokenType_NL

  %token EulTokenType_ERROR
  %token EulTokenType_EOF
//endregion


//region NON TERMINALS
  %token EulTokenType_VAR_DECLARATION //Valid children: only EulSyntaxType_PARAMETER_DECLARATION
  %token EulTokenType_PROGRAM
  %token EulTokenType_SOURCE_FILE
//endregion




//region OPERATOR PRECEDENCE
%right EulTokenType_TILDE EulTokenType_NOT EulTokenType_DECREASE EulTokenType_INCREASE
%left EulTokenType_DOT
%left EulTokenType_PERCENT EulTokenType_STAR EulTokenType_SLASH
%left EulTokenType_PLUS EulTokenType_MINUS
%left EulTokenType_LSHIFT EulTokenType_RSHIFT
%left EulTokenType_LESS EulTokenType_LESS_EQUALS EulTokenType_MORE EulTokenType_MORE_EQUALS
%left EulTokenType_NOT_EQUALS EulTokenType_NOT_SAME EulTokenType_EQUALS EulTokenType_SAME
%left EulTokenType_BIN_AND
%left EulTokenType_XOR
%left EulTokenType_BIN_OR
%left EulTokenType_AND
%left EulTokenType_OR
%right EulTokenType_QUESTION EulTokenType_COLON
%right EulTokenType_ASSIGN EulTokenType_ASSIGN_MOD EulTokenType_ASSIGN_XOR EulTokenType_ASSIGN_AND EulTokenType_ASSIGN_STAR EulTokenType_ASSIGN_MINUS EulTokenType_ASSIGN_PLUS EulTokenType_ASSIGN_OR EulTokenType_ASSIGN_DIV EulTokenType_ASSIGN_LSHIFT EulTokenType_ASSIGN_RSHIFT
%left EulTokenType_COMMA
//endregion


%start EulSyntaxType_SOURCE_FILE




//=============================================           =============================================
//=============================================   RULES   =============================================
//=============================================           =============================================
%%



//========================= GROUPS OF TOKENTS =============================
EulSyntaxType_VAR_KEYWORD
    : EulTokenType_VAR
    | EulTokenType_CONST
    | EulTokenType_VAL
    ;

EulSyntaxType_LITERAL
    : EulTokenType_INT
    | EulTokenType_FLOAT
    | EulTokenType_STRING
    | EulTokenType_CHAR
    ;


EulSyntaxType_INFIX
    : EulTokenType_PLUS
    | EulTokenType_MINUS
    | EulTokenType_NOT_EQUALS
    | EulTokenType_NOT_SAME
    | EulTokenType_PERCENT
    | EulTokenType_ASSIGN_MOD
    | EulTokenType_XOR
    | EulTokenType_ASSIGN_XOR
    | EulTokenType_BIN_AND
    | EulTokenType_AND
    | EulTokenType_ASSIGN_AND
    | EulTokenType_STAR
    | EulTokenType_ASSIGN_STAR
    | EulTokenType_ASSIGN_MINUS
    | EulTokenType_ASSIGN
    | EulTokenType_EQUALS
    | EulTokenType_SAME
    | EulTokenType_ASSIGN_PLUS
    | EulTokenType_BIN_OR
    | EulTokenType_OR
    | EulTokenType_ASSIGN_OR
    | EulTokenType_SLASH
    | EulTokenType_ASSIGN_DIV
    | EulTokenType_DOT
    | EulTokenType_LESS
    | EulTokenType_LESS_EQUALS
    | EulTokenType_LSHIFT
    | EulTokenType_ASSIGN_LSHIFT
    | EulTokenType_MORE
    | EulTokenType_MORE_EQUALS
    | EulTokenType_RSHIFT
    | EulTokenType_ASSIGN_RSHIFT
    ;

EulSyntaxType_PREFIX
    : EulTokenType_MINUS
    | EulTokenType_TILDE
    | EulTokenType_NOT
    | EulTokenType_DECREASE
    | EulTokenType_INCREASE
    ;

EulSyntaxType_SUFFIX
    : EulTokenType_DECREASE
    | EulTokenType_INCREASE
    ;




//========================== ROOT STRUCTURES ==============================
EulSyntaxType_SOURCE_FILE:
    EulSyntaxType_STATEMENTS EulTokenType_EOF {
        //compiler->src.root = $1->asNode;
        printf("EulSyntaxType_SOURCE_FILE Parsed successfully\n");

        compiler->currentSource->statements = *($1->value.asList);

        return 0;
    }



//============================== STATEMENTS  ==============================
EulSyntaxType_STATEMENTS:
    EulSyntaxType_STATEMENT EulSyntaxType_STATEMENTS {
        printf("EulSyntaxType_STATEMENTS: EulSyntaxType_STATEMENT EulSyntaxType_STATEMENTS\n");

        //No token is being created here. We just append the incoming statement to an existing list
        EulNodeList_unshift($2->value.asList, $1);
        $$ = $2;
    } |
    EulSyntaxType_STATEMENT {
        printf("EulSyntaxType_STATEMENTS: EulSyntaxType_STATEMENT\n");

        //create a List-type token (to hold the statementS) and push the first element
        $$ = (EulToken*) malloc(sizeof(EulToken));
        EulToken_initListWith($$, $1);
    }


//TODO
EulSyntaxType_STATEMENT:
    EulSyntaxType_VAR_KEYWORD EulSyntaxType_PARAMETER_LIST EulTokenType_SEMICOLON {
        printf("EulSyntaxType_STATEMENT: EulSyntaxType_VAR_KEYWORD EulSyntaxType_PARAMETER_LIST\n");

        $$ = (EulToken*) malloc(sizeof(EulToken)); //TODO free this somewhere
        //EulToken_initVarDeclaration($$, EulTokenType_VAR_DECLARATION);
    } |

    EulSyntaxType_EXPRESSION EulTokenType_SEMICOLON {
        $$ = (EulToken*) malloc(sizeof(EulToken));
        //TODO
    }





//============================== EXPRESSIONS  ==============================
EulSyntaxType_EXPRESSION:
    EulSyntaxType_LITERAL   { $$ = $1; } |
    EulTokenType_ID         { $$ = $1; } |
    EulTokenType_PARENTHESIS_OPEN EulSyntaxType_EXPRESSION EulTokenType_PARENTHESIS_CLOSE        { $$ = $1; } |

    EulSyntaxType_EXPRESSION EulSyntaxType_INFIX EulSyntaxType_EXPRESSION {
        //TODO
    }

    EulSyntaxType_PREFIX EulSyntaxType_EXPRESSION {
        //TODO
    }

    EulSyntaxType_EXPRESSION EulSyntaxType_SUFFIX {
        //TODO
    }





//======================== VAR DECLARATIONS AND FUNCTION PARAMETERS ============================


//TODO
EulSyntaxType_PARAMETER_DECLARATION:
    EulTokenType_ID EulTokenType_ASSIGN EulSyntaxType_EXPRESSION {

    } |
    EulTokenType_ID {

    }



EulSyntaxType_PARAMETER_LIST:
    EulSyntaxType_PARAMETER_LIST EulTokenType_COMMA EulSyntaxType_PARAMETER_DECLARATION {
        //TODO
    } |
    EulSyntaxType_PARAMETER_DECLARATION {
        //TODO
    }

%%


int yyerror(yyscan_t scanner, const char *msg) {
  printf("YYERROR!!! %s\n", msg);
  return 0;
}
