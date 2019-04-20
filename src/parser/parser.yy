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
    class EulScope;
    class EulType;
    class EulOperator;

    namespace llvm {
        class Value;
        class Type;
        class AllocaInst;
        class BasicBlock;
        class Function;
    }
    //endregion


    # include <string>
    # include <map>
    # include <forward_list>
    # include <vector>
    #include <memory>

    #include "../core/EulNode/enums/EulNodeType.h"
    #include "../core/EulNode/EulNode.h"
    #include "../core/EulNode/reuseables/ValueNode.h"
    #include "../core/EulNode/leaf_nodes/EulIntNode/EulIntNode.h"
    #include "../core/EulNode/leaf_nodes/EulFloatNode/EulFloatNode.h"
    #include "../core/EulNode/leaf_nodes/EulCharNode/EulCharNode.h"
    #include "../core/EulNode/leaf_nodes/EulBooleanNode/EulBooleanNode.h"
    #include "../core/EulNode/leaf_nodes/EulStringNode/EulStringNode.h"
    #include "../core/EulNode/leaf_nodes/EulSymbolNameNode/EulSymbolNameNode.h"
    #include "../core/EulNode/enums/EulTypeEnum.h"
    #include "../core/EulNode/types/EulType/EulType.h"
    #include "../core/EulNode/types/EulIntegerType/EulIntegerType.h"
    #include "../core/EulNode/types/EulFloatType/EulFloatType.h"
    #include "../core/EulNode/types/EulCharType/EulCharType.h"
    #include "../core/EulNode/types/EulStringType/EulStringType.h"
    #include "../core/EulNode/types/EulNamedType/EulNamedType.h"
    #include "../core/EulNode/types/EulVoidType/EulVoidType.h"
    #include "../core/EulNode/types/EulAnyType/EulAnyType.h"
    #include "../core/EulNode/types/EulBooleanType/EulBooleanType.h"
    #include "../core/EulNode/types/EulFunctionType/EulFunctionType.h"

    #include "../core/EulNode/enums/EulStatementType.h"
    #include "../core/EulNode/statements/EulStatement/EulStatement.h"
    #include "../core/EulNode/statements/EulImportStatement/EulImportStatement.h"
    #include "../core/EulNode/statements/EulExportStatement/EulExportStatement.h"
    #include "../core/EulNode/statements/ReturnStatement/ReturnStatement.h"

    #include "../core/EulNode/reuseables/ValueNode.h"
    #include "../core/EulNode/enums/EulExpressionType.h"
    #include "../core/EulNode/expressions/EulExpression/EulExpression.h"
    #include "../core/EulNode/expressions/EulInfixExp/EulInfixExp.h"
    #include "../core/EulNode/expressions/EulSuffixExp/EulSuffixExp.h"
    #include "../core/EulNode/expressions/EulPrefixExp/EulPrefixExp.h"
    #include "../core/EulNode/expressions/EulFunctionCallExp/EulFunctionCallExp.h"
    #include "../core/EulNode/expressions/EulArrayAccessExp/EulArrayAccessExp.h"
    #include "../core/EulNode/statements/EulExpStatement/EulExpStatement.h"


    #include "../core/EulNode/reuseables/VarDeclaration/VarDeclaration.h"
    #include "../core/EulNode/statements/VarDeclarationStatement/VarDeclarationStatement.h"

    #include "../core/misc/EulSymbol/EulSymbol.h"
    #include "../core/misc/EulScope/EulScope.h"
    #include "../core/EulNode/reuseables/EulCodeBlock/EulCodeBlock.h"
    #include "../core/EulNode/reuseables/EulFunction/EulFunction.h"
    #include "../core/EulNode/reuseables/EulExpressionCodeBlock/EulExpressionCodeBlock.h"

    #include "../core/EulNode/statements/EulIfStatement/EulIfStatement.h"
    #include "../core/EulNode/statements/EulWhileStatement/EulWhileStatement.h"
    #include "../core/EulNode/statements/EulFuncDeclarationStatement/EulFuncDeclarationStatement.h"


    #include "../core/Compiler/EulSourceFile/EulSourceFile.h"
    #include "../core/Compiler/EulProgram/EulNativeTypes.h"
    #include "../core/Compiler/EulProgram/EulProgram.h"
    #include "../core/Compiler/EulError/EulError.h"
    #include "../core/Compiler/Compiler.h"
    #include "../parser/EulParsingContext.h"
    #include "../parser/EulParsingUtils.h"

    #include "../core/EulNode/operators/EulOperator/EulOperator.h"
    #include "../core/EulNode/operators/assignments/AssignAndOperator/AssignAndOperator.h"
    #include "../core/EulNode/operators/assignments/AssignDivOperator/AssignDivOperator.h"
    #include "../core/EulNode/operators/assignments/AssignLeftShiftOperator/AssignLeftShiftOperator.h"
    #include "../core/EulNode/operators/assignments/AssignMinusOperator/AssignMinusOperator.h"
    #include "../core/EulNode/operators/assignments/AssignModOperator/AssignModOperator.h"
    #include "../core/EulNode/operators/assignments/AssignOperator/AssignOperator.h"
    #include "../core/EulNode/operators/assignments/AssignOrOperator/AssignOrOperator.h"
    #include "../core/EulNode/operators/assignments/AssignPlusOperator/AssignPlusOperator.h"
    #include "../core/EulNode/operators/assignments/AssignRightShiftOperator/AssignRightShiftOperator.h"
    #include "../core/EulNode/operators/assignments/AssignStarOperator/AssignStarOperator.h"
    #include "../core/EulNode/operators/assignments/AssignXorOperator/AssignXorOperator.h"
    #include "../core/EulNode/operators/assignments/IncreaseOperator/IncreaseOperator.h"
    #include "../core/EulNode/operators/assignments/DecreaseOperator/DecreaseOperator.h"

    #include "../core/EulNode/operators/logical/OrOperator/OrOperator.h"
    #include "../core/EulNode/operators/logical/NotOperator/NotOperator.h"
    #include "../core/EulNode/operators/logical/AndOperator/AndOperator.h"
    #include "../core/EulNode/operators/logical/EqualsOperator/EqualsOperator.h"
    #include "../core/EulNode/operators/logical/NotEqualsOperator/NotEqualsOperator.h"
    #include "../core/EulNode/operators/logical/NotSameOperator/NotSameOperator.h"
    #include "../core/EulNode/operators/logical/XorOperator/XorOperator.h"
    #include "../core/EulNode/operators/logical/SameOperator/SameOperator.h"
    #include "../core/EulNode/operators/logical/LessOperator/LessOperator.h"
    #include "../core/EulNode/operators/logical/LessEqualsOperator/LessEqualsOperator.h"
    #include "../core/EulNode/operators/logical/MoreOperator/MoreOperator.h"
    #include "../core/EulNode/operators/logical/MoreEqualsOperator/MoreEqualsOperator.h"

    #include "../core/EulNode/operators/arithmetic/BinAndOperator/BinAndOperator.h"
    #include "../core/EulNode/operators/arithmetic/BinOrOperator/BinOrOperator.h"
    #include "../core/EulNode/operators/arithmetic/LeftShiftOperator/LeftShiftOperator.h"
    #include "../core/EulNode/operators/arithmetic/MinusOperator/MinusOperator.h"
    #include "../core/EulNode/operators/arithmetic/PercentOperator/PercentOperator.h"
    #include "../core/EulNode/operators/arithmetic/PlusOperator/PlusOperator.h"
    #include "../core/EulNode/operators/arithmetic/RightShiftOperator/RightShiftOperator.h"
    #include "../core/EulNode/operators/arithmetic/SlashOperator/SlashOperator.h"
    #include "../core/EulNode/operators/arithmetic/StarOperator/StarOperator.h"
    #include "../core/EulNode/operators/arithmetic/TildeOperator/TildeOperator.h"


    #include "../core/EulNode/operators/misc/DotOperator/DotOperator.h"
    #include "../core/EulNode/operators/misc/ColonOperator/ColonOperator.h"
    #include "../core/EulNode/operators/misc/QuestionOperator/QuestionOperator.h"

    #include "../core/EulNode/operators/EulOperator/EulOperators.h"




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
    ELSE
    ELSE_IF
    FOR
    WHILE
    VAR
    CONST
    VAL
    RETURN
    FUNC
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
    <std::shared_ptr<EulIntNode>> INT
    <std::shared_ptr<EulFloatNode>> FLOAT
    <std::shared_ptr<EulStringNode>> STRING
    <std::shared_ptr<EulCharNode>> CHAR
    <std::shared_ptr<EulBooleanNode>> BOOLEAN
    <std::shared_ptr<EulSymbolNameNode>> ID
;

%destructor {  } <*>




%locations


%printer { yyoutput << $$; } <*>;





//region NON TERMINALS
%type  <EulSourceFile*> source_file

%type  <std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>>> statements
%type  <std::shared_ptr<EulStatement>> statement

%type  <std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>>> parameter_declarations
%type  <std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>>> func_params
%type  <std::shared_ptr<VarDeclaration>> parameter_declaration
%type  <std::shared_ptr<EulType>> eul_type

%type  <std::shared_ptr<ValueNode>> expression
%type  <std::shared_ptr<std::vector<std::shared_ptr<ValueNode>>>> expressions

%type  <std::shared_ptr<EulCodeBlock>> block
%type  <std::shared_ptr<EulCodeBlock>> block_or_statement

//if block related
%type  <std::shared_ptr<EulIfStatement>> if_block
%type  <std::shared_ptr<std::vector<std::shared_ptr<EulExpressionCodeBlock>>>> else_if_sub_blocks
%type  <std::shared_ptr<EulExpressionCodeBlock>> else_if_sub_block


//loops
%type  <std::shared_ptr<EulWhileStatement>> while_block

//function related
%type  <std::shared_ptr<VarDeclaration>> func_param_declaration
%type  <std::shared_ptr<EulFuncDeclarationStatement>> func_decl


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
    : lines statements END {
        ctx->sourceFile->statements = $2;
        $$ = nullptr;
        return 0;
    }
    | END { $$ = nullptr; return 0; }
    ;



//============================== MISC ==============================
lines:
    lines NL |
    %empty
    ;

lines_or_semicolon:
    NL lines |
    SEMICOLON lines |
    END
    ;

var_keyword
    : VAR { $$ = token::VAR; }
    | CONST { $$ = token::CONST; }
    | VAL { $$ = token::VAL; }
    ;


//============================== STATEMENT BASICS  ==============================
statements:
    statements statement {
        if ($1 == nullptr) $1 = std::make_shared<std::vector<std::shared_ptr<EulStatement>>>();
        if ($2!=nullptr) $1->push_back($2);
        $$ = $1;
    } |
    statement {
        $$ = std::make_shared<std::vector<std::shared_ptr<EulStatement>>>();
        if ($1!=nullptr) $$->push_back($1);
    }
    ;


statement:
    var_keyword parameter_declarations lines_or_semicolon {
        $$ = std::make_shared<VarDeclarationStatement>($1, $2);
        ctx->currentScope->declare(static_cast<VarDeclarationStatement*>($$.get()));
    } |

    expression lines_or_semicolon {
        $$ = std::make_shared<EulExpStatement>($1);
    } |

    RETURN expression lines_or_semicolon {
        $$ = std::make_shared<ReturnStatement>($2);
    } |

    RETURN lines_or_semicolon {
        $$ = std::make_shared<ReturnStatement>(nullptr);
    } |
    if_block { $$ = $1; } |
    while_block { $$ = $1; } |
    func_decl { $$ = $1; }
    ;

block_or_statement:
    open_scope statement {
        //1. make a vector with the statement
        auto statementList = std::make_shared<std::vector<std::shared_ptr<EulStatement>>>();
        statementList->push_back($2);

        //2. Create the block object
        $$ = std::make_shared<EulCodeBlock>(statementList, ctx->currentScope);
        ctx->popScope();
    } |
    block { $$ = $1; }
    ;


block:
    CURLY_OPEN lines open_scope statements CURLY_CLOSE lines {
        $$ = std::make_shared<EulCodeBlock>($4, ctx->currentScope);
        ctx->popScope();
    } |
    CURLY_OPEN lines CURLY_CLOSE lines {
        $$ = std::make_shared<EulCodeBlock>(
            std::make_shared<std::vector<std::shared_ptr<EulStatement>>>(),
            ctx->currentScope
        );
    }
    ;



//============================== IF STATEMENT ==============================
if_block:
    IF expression block else_if_sub_blocks {
        $$ = std::make_shared<EulIfStatement>($2, $3, $4, nullptr);
    } |
    IF expression block else_if_sub_blocks ELSE block_or_statement {
        $$ = std::make_shared<EulIfStatement>($2, $3, $4, $6);
    }
    ;

else_if_sub_block:
    ELSE_IF expression block {
        $$ = std::make_shared<EulExpressionCodeBlock>($2, $3);
    }
    ;

else_if_sub_blocks:
    else_if_sub_blocks else_if_sub_block {
        if ($1 == nullptr) $1 = std::make_shared<std::vector<std::shared_ptr<EulExpressionCodeBlock>>>();
        if ($2!=nullptr) $1->push_back($2);
        $$ = $1;
    } |
    %empty { $$ = nullptr; }
    ;



//============================== LOOPS ==============================
while_block:
    WHILE expression block {
        $$ = std::make_shared<EulWhileStatement>($2, $3);
    }
    ;



//============================== FUNCTION RELATED ==============================
func_param_declaration:
    ID COLON eul_type {
        $$ = std::make_shared<VarDeclaration>($1, $3, nullptr);
    }
    ;

func_params:
    func_params COMMA func_param_declaration {
        if ($1 == nullptr) $1 = std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>();
        $1->push_back($3);
        $$ = $1;
    } |
    func_param_declaration {
        $$ = std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>();
        $$->push_back($1);
    } |
    %empty { $$ = nullptr; }
    ;

func_decl:
    FUNC ID PARENTHESIS_OPEN func_params PARENTHESIS_CLOSE block {
        auto funcType = std::make_shared<EulFunctionType>(ctx->compiler->program.nativeTypes.voidType, $4);
        auto func = std::make_shared<EulFunction>(funcType, $4, $6);
        ctx->currentScope->declare(
            $2->name,
            std::make_shared<EulSymbol>(token::CONST, funcType, func)
        );
        $$ = std::make_shared<EulFuncDeclarationStatement>(func, $2);
    } |
    FUNC ID PARENTHESIS_OPEN func_params PARENTHESIS_CLOSE COLON eul_type block {
        auto funcType = std::make_shared<EulFunctionType>($7, $4);
        auto func = std::make_shared<EulFunction>(funcType, $4, $8);
        ctx->currentScope->declare(
            $2->name,
            std::make_shared<EulSymbol>(token::CONST, funcType, func)
        );
        $$ = std::make_shared<EulFuncDeclarationStatement>(func, $2);
    }
    ;


//======================== VAR DECLARATIONS AND FUNCTION PARAMETERS ============================
eul_type:
    ID {

        //1. Find if the symbol already exists in this scope, or any super scope.
        std::shared_ptr<EulSymbol> alreadyExisting = ctx->currentScope->get($1->name);

        //2a. If it does not already exist, create one and return it.
        // But do NOT declare it as a symbol in the scope. This action does not belong here.
        if (alreadyExisting==nullptr) $$ = std::make_shared<EulNamedType>($1->name);

        //2b. If the symbol is found, check that it is really a EulType, and return it.
        else if (EulType::isEulType(alreadyExisting->value.get())) {
            $$ = std::dynamic_pointer_cast<EulType>(alreadyExisting->value);
        }

        //2c. found but not a type? add an error!
        else {
            ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, "Type expected, but other token type was found."));
            $$ = nullptr;
        }
    }
    ;

parameter_declaration:
    ID ASSIGN expression {
        $$ = std::make_shared<VarDeclaration>($1, nullptr, $3);
    } |
    ID {
        $$ = std::make_shared<VarDeclaration>($1, nullptr, nullptr);
    } |
    ID COLON eul_type {
        $$ = std::make_shared<VarDeclaration>($1, $3, nullptr);
    } |
    ID COLON eul_type ASSIGN expression {
        $$ = std::make_shared<VarDeclaration>($1, $3, $5);
    }
    ;


parameter_declarations:
    parameter_declarations COMMA parameter_declaration {
        if ($1 == nullptr) $1 = std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>();
        $1->push_back($3);
        $$ = $1;
    } |
    parameter_declaration {
        $$ = std::make_shared<std::vector<std::shared_ptr<VarDeclaration>>>();
        $$->push_back($1);
    }
    ;

//============================== EXPRESSIONS  ==============================
expression
    : INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | BOOLEAN { $$ = $1; }
    | STRING { $$ = $1; }
    | CHAR { $$ = $1; }
    | ID   { $$ = $1; }

    | expression PLUS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.plusOperator, $3); }
    | expression MINUS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.minusOperator, $3); }
    | expression NOT_EQUALS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.notEqualsOperator, $3); }
    | expression NOT_SAME expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.notSameOperator, $3); }
    | expression PERCENT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.percentOperator, $3); }
    | expression ASSIGN_MOD expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignModOperator, $3); }
    | expression XOR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.xorOperator, $3); }
    | expression ASSIGN_XOR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignXorOperator, $3); }
    | expression BIN_AND expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.binAndOperator, $3); }
    | expression AND expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.andOperator, $3); }
    | expression ASSIGN_AND expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignAndOperator, $3); }
    | expression STAR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.starOperator, $3); }
    | expression ASSIGN_STAR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignStarOperator, $3); }
    | expression ASSIGN_MINUS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignMinusOperator, $3); }
    | expression ASSIGN expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignOperator, $3); }
    | expression EQUALS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.equalsOperator, $3); }
    | expression SAME expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.sameOperator, $3); }
    | expression ASSIGN_PLUS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignPlusOperator, $3); }
    | expression BIN_OR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.binOrOperator, $3); }
    | expression OR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.orOperator, $3); }
    | expression ASSIGN_OR expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignOrOperator, $3); }
    | expression SLASH expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.slashOperator, $3); }
    | expression ASSIGN_DIV expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignDivOperator, $3); }
    | expression DOT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.dotOperator, $3); }
    | expression LESS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.lessOperator, $3); }
    | expression LESS_EQUALS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.lessEqualsOperator, $3); }
    | expression LSHIFT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.leftShiftOperator, $3); }
    | expression ASSIGN_LSHIFT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignLeftShiftOperator, $3); }
    | expression MORE expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.moreOperator, $3); }
    | expression MORE_EQUALS expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.moreEqualsOperator, $3); }
    | expression RSHIFT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.rightShiftOperator, $3); }
    | expression ASSIGN_RSHIFT expression { $$ = std::make_shared<EulInfixExp>($1, &EUL_OPERATORS.assignRightShiftOperator, $3); }

    | PARENTHESIS_OPEN expression PARENTHESIS_CLOSE        { $$ = $2; }
    | expression PARENTHESIS_OPEN expressions PARENTHESIS_CLOSE        {  $$ = std::make_shared<EulFunctionCallExp>($1, $3); }
    | expression SQUARE_OPEN expression SQUARE_CLOSE        { $$ = std::make_shared<EulArrayAccessExp>($1, $3 ); }


    | MINUS expression { $$ = std::make_shared<EulPrefixExp>(&EUL_OPERATORS.minusOperator, $2); } %prec NOT
    | TILDE expression { $$ = std::make_shared<EulPrefixExp>(&EUL_OPERATORS.tildeOperator, $2); }
    | NOT expression { $$ = std::make_shared<EulPrefixExp>(&EUL_OPERATORS.notOperator, $2); }
    | DECREASE expression { $$ = std::make_shared<EulPrefixExp>(&EUL_OPERATORS.decreaseOperator, $2); }
    | INCREASE expression { $$ = std::make_shared<EulPrefixExp>(&EUL_OPERATORS.increaseOperator, $2); }

    | expression DECREASE { $$ = std::make_shared<EulSuffixExp>($1, &EUL_OPERATORS.decreaseOperator); }
    | expression INCREASE { $$ = std::make_shared<EulSuffixExp>($1, &EUL_OPERATORS.increaseOperator); }
    ;



expressions:
    expressions COMMA expression {
        if ($1 == nullptr) $1 = std::make_shared<std::vector<std::shared_ptr<ValueNode>>>();
        $1->push_back($3);
        $$ = $1;
    } |
    expression {
        $$ = std::make_shared<std::vector<std::shared_ptr<ValueNode>>>();
        $$->push_back($1);
    } |
    %empty { $$ = nullptr; }
    ;


//================================= ACTION NON TERMINALS =========================
    open_scope:
      %empty  { ctx->pushScope(); }
    ;

    //close_scope:
    //  %empty  { ctx->popScope(); }
    //;
%%


void yy::EulParser::error( const location_type &l, const std::string &err_message ) {
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
