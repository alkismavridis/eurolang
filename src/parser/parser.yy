%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parser_class_name {EulParser}


%code requires
{
    //region UGGLY FORWARD DECLARATIONS
    class EulScanner;
    class EulCodeGenContext;
    namespace llvm {
        class Value;
        class Module;
        class LLVMContext;
        class Type;
        class ConstantFolder;
        class IRBuilderDefaultInserter;
        template<typename T, typename Inserter> class IRBuilder;
    }
    //endregion


    # include <string>
    # include <map>
    # include <forward_list>
    # include <vector>
    #include <memory>

    #include "../core/Operators/EulOperator.h"

    #include "../core/EulToken/EulTokenType.h"
    #include "../core/EulToken/EulToken.h"
    #include "../core/EulToken/EulIntToken.h"
    #include "../core/EulToken/EulFloatToken.h"
    #include "../core/EulToken/EulCharToken.h"
    #include "../core/EulToken/EulStringToken.h"
    #include "../core/EulToken/EulIdToken.h"
    #include "../core/EulAst/EulAstType.h"
    #include "../core/EulAst/EulAst.h"
    #include "../core/EulAst/EulType/EulType.h"
    #include "../core/EulAst/EulType/LateDefinedType.h"
    #include "../core/EulAst/EulSymbol/EulSymbol.h"
    #include "../core/EulAst/EulStatement/EulStatementType.h"
    #include "../core/EulAst/EulStatement/EulStatement.h"
    #include "../core/EulAst/EulStatement/EulImportStatement.h"
    #include "../core/EulAst/EulStatement/EulExportStatement.h"
    #include "../core/EulAst/EulStatement/ReturnStatement.h"

    #include "../core/EulAst/EulExpression/EulExpressionType.h"
    #include "../core/EulAst/EulExpression/EulExpression.h"
    #include "../core/EulAst/EulExpression/EulInfixExp.h"
    #include "../core/EulAst/EulExpression/EulSuffixExp.h"
    #include "../core/EulAst/EulExpression/EulPrefixExp.h"
    #include "../core/EulAst/EulExpression/EulTokenExp.h"
    #include "../core/EulAst/EulExpression/EulFunctionCallExp.h"
    #include "../core/EulAst/EulExpression/EulArrayAccessExp.h"
    #include "../core/EulAst/EulStatement/EulExpStatement.h"


    #include "../core/EulAst/EulDeclaration/VarDeclaration.h"
    #include "../core/EulAst/EulStatement/VarDeclarationStatement.h"

    #include "../core/EulScope/EulScope.h"
    #include "../core/EulSourceFile/EulSourceFile.h"
    #include "../core/EulProgram/EulProgram.h"
    #include "../core/Compiler/EulError/EulError.h"
    #include "../core/Compiler/Compiler.h"
    #include "../parser/EulParsingContext.h"
    #include "../parser/EulParsingUtils.h"



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
%parse-param { EulParsingContext  *ctx  }
%lex-param   { EulParsingContext  *ctx }


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
%define parse.assert



%token
    END  0  "end of file"
    IF
    FOR
    WHILE
    VAR
    CONST
    VAL
    RETURN
    NAMESPACE

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

%destructor {  } <*>




%locations


%printer { yyoutput << $$; } <*>;





//region NON TERMINALS
%type  <EulSourceFile*> source_file

%type  <std::vector<EulStatement*>*> statements
%type  <EulStatement*> statement

%type  <std::vector<VarDeclaration*>*> parameter_declarations
%type  <VarDeclaration*> parameter_declaration
%type  <EulType*> eul_type

%type  <EulToken*> expression
%type  <std::vector<EulToken*>*> expressions

%type  <int> var_keyword
//endregion



//region OPERATOR PRECEDENCE

%right ASSIGN ASSIGN_MOD ASSIGN_XOR ASSIGN_AND ASSIGN_STAR ASSIGN_MINUS ASSIGN_PLUS ASSIGN_OR ASSIGN_DIV ASSIGN_LSHIFT ASSIGN_RSHIFT
%right QUESTION COLON
%left OR
%left AND
%left BIN_OR
%left XOR
%left BIN_AND
%left NOT_EQUALS NOT_SAME EQUALS SAME
%left LESS LESS_EQUALS MORE MORE_EQUALS
%left LSHIFT RSHIFT
%left PLUS MINUS
%left PERCENT STAR SLASH
%right TILDE NOT DECREASE INCREASE
%left DOT
%precedence PARENTHESIS_OPEN SQUARE_OPEN
//endregion



%start source_file



//=============================================           =============================================
//=============================================   RULES   =============================================
//=============================================           =============================================
%%



//========================== ROOT STRUCTURES ==============================
source_file
    : statements END {
        ctx->sourceFile->statements = $1;
        $$ = nullptr;
        return 0;
    }
    | END { $$ = nullptr; return 0; }
    ;



//============================== STATEMENTS  ==============================
statements:
    statements statement {
        if ($1 == nullptr) $1 = new std::vector<EulStatement*>();
        if ($2!=nullptr) $1->push_back($2);
        $$ = $1;
    } |
    statement {
        $$ = new std::vector<EulStatement*>();
        if ($1!=nullptr) $$->push_back($1);
    }



var_keyword
    : VAR { $$ = token::VAR; }
    | CONST { $$ = token::CONST; }
    | VAL { $$ = token::VAL; }
    ;

statement:
    var_keyword parameter_declarations SEMICOLON {
        $$ = new VarDeclarationStatement($1, $2);
        //EulParserUtils::addSymbolsToSourceFile($1, $2, ctx);
    } |

    expression SEMICOLON {
        $$ = new EulExpStatement($1);
    } |

    RETURN expression SEMICOLON {
        $$ = new ReturnStatement($2);
    } |

    RETURN SEMICOLON {
        $$ = new ReturnStatement(nullptr);
    } |

    NL {
        $$ = nullptr;
    }





//============================== EXPRESSIONS  ==============================
expression
    : INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | STRING { $$ = $1; }
    | CHAR { $$ = $1; }
    | ID   { $$ = $1; }

    | expression PLUS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.plusOperator, $3); }
    | expression MINUS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.minusOperator, $3); }
    | expression NOT_EQUALS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.notEqualsOperator, $3); }
    | expression NOT_SAME expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.notSameOperator, $3); }
    | expression PERCENT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.percentOperator, $3); }
    | expression ASSIGN_MOD expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignModOperator, $3); }
    | expression XOR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.xorOperator, $3); }
    | expression ASSIGN_XOR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignXorOperator, $3); }
    | expression BIN_AND expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.binAndOperator, $3); }
    | expression AND expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.andOperator, $3); }
    | expression ASSIGN_AND expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignAndOperator, $3); }
    | expression STAR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.starOperator, $3); }
    | expression ASSIGN_STAR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignStarOperator, $3); }
    | expression ASSIGN_MINUS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignMinusOperator, $3); }
    | expression ASSIGN expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignOperator, $3); }
    | expression EQUALS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.equalsOperator, $3); }
    | expression SAME expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.sameOperator, $3); }
    | expression ASSIGN_PLUS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignPlusOperator, $3); }
    | expression BIN_OR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.binOrOperator, $3); }
    | expression OR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.orOperator, $3); }
    | expression ASSIGN_OR expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignOrOperator, $3); }
    | expression SLASH expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.slashOperator, $3); }
    | expression ASSIGN_DIV expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignDivOperator, $3); }
    | expression DOT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.dotOperator, $3); }
    | expression LESS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.lessOperator, $3); }
    | expression LESS_EQUALS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.lessEqualsOperator, $3); }
    | expression LSHIFT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.leftShiftOperator, $3); }
    | expression ASSIGN_LSHIFT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignLeftShiftOperator, $3); }
    | expression MORE expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.moreOperator, $3); }
    | expression MORE_EQUALS expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.moreEqualsOperator, $3); }
    | expression RSHIFT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.rightShiftOperator, $3); }
    | expression ASSIGN_RSHIFT expression { $$ = new EulInfixExp($1, &EUL_OPERATORS.assignRightShiftOperator, $3); }

    | PARENTHESIS_OPEN expression PARENTHESIS_CLOSE        { $$ = $2; }
    | expression PARENTHESIS_OPEN expressions PARENTHESIS_CLOSE        {  $$ = new EulFunctionCallExp($1, $3); }
    | expression SQUARE_OPEN expression SQUARE_CLOSE        { $$ = new EulArrayAccessExp($1, $3 ); }


    | MINUS expression { $$ = new EulPrefixExp(&EUL_OPERATORS.minusOperator, $2); } %prec NOT
    | TILDE expression { $$ = new EulPrefixExp(&EUL_OPERATORS.tildeOperator, $2); }
    | NOT expression { $$ = new EulPrefixExp(&EUL_OPERATORS.notOperator, $2); }
    | DECREASE expression { $$ = new EulPrefixExp(&EUL_OPERATORS.decreaseOperator, $2); }
    | INCREASE expression { $$ = new EulPrefixExp(&EUL_OPERATORS.increaseOperator, $2); }

    | expression DECREASE { $$ = new EulSuffixExp($1, &EUL_OPERATORS.decreaseOperator); }
    | expression INCREASE { $$ = new EulSuffixExp($1, &EUL_OPERATORS.increaseOperator); }
    ;



expressions:
    expressions COMMA expression {
        if ($1 == nullptr) $1 = new std::vector<EulToken*>();
        $1->push_back($3);
        $$ = $1;
    } |
    expression {
        $$ = new std::vector<EulToken*>();
        $$->push_back($1);
    } |
    %empty { $$ = nullptr; }
    ;




//======================== VAR DECLARATIONS AND FUNCTION PARAMETERS ============================
eul_type:
    ID {
        $$ = EulParsingUtils::createEulType(ctx, $1->name);
        delete $1;
    }
    ;

parameter_declaration:
    ID ASSIGN expression {
        $$ = new VarDeclaration($1, nullptr, $3);
    } |
    ID {
        $$ = new VarDeclaration($1, nullptr, nullptr);
    } |
    ID COLON eul_type {
        $$ = new VarDeclaration($1, $3, nullptr);
    } |
    ID COLON eul_type ASSIGN expression {
        $$ = new VarDeclaration($1, $3, $5);
    }
    ;



parameter_declarations:
    parameter_declarations COMMA parameter_declaration {
        if ($1 == nullptr) $1 = new std::vector<VarDeclaration*>();
        $1->push_back($3);
        $$ = $1;
    } |
    parameter_declaration {
        $$ = new std::vector<VarDeclaration*>();
        $$->push_back($1);
    }
    ;
%%


    void yy::EulParser::error( const location_type &l, const std::string &err_message ) {
       std::cerr << "Error: " << err_message << " at " << l << "\n";
    }