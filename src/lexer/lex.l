%{ /* -*- C++ -*- */
    # include <cerrno>
    # include <climits>
    # include <cstdlib>
    # include <string>
    # include "EulParser.tab.hh"
    # include "../core/Compiler/EulError/EulError.h"
    # include "../lexer/EulScanner.h"
    # include "../lexer/EulScanner.impl.h"

    #undef  YY_DECL
    #define YY_DECL int EulScanner::yylex( yy::EulParser::semantic_type * const yylval, yy::EulParser::location_type *loc, EulParsingContext  *ctx )

    /* define yyterminate as this instead of NULL */
    #define yyterminate() return( EulParser::token::END )

    /* msvc2010 requires that we exclude this header file. */
    #define YY_NO_UNISTD_H

    /* update location on matching */
    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="EulScanner"
%option noyywrap
%option c++


ASC     [\x00-\x7f]
ASCN    [\x00-\t\v-\x7f]
U       [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]

ANY_UNICODE    			{ASC}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
ANY_UNICODE_NO_NL   {ASCN}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
NON_ASCII  					{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}

WORD_TAIL	([a-zA-Z0-9_]|{NON_ASCII})

%%




[ \t]+     loc->step();

[1-9][0-9]*([su][0-9]*)? {
    yylval->build<std::shared_ptr<EulIntToken>>() = std::make_shared<EulIntToken>(yytext);
    return yy::EulParser::token::INT;
}

"0"([su][0-9]*)? {
    yylval->build<std::shared_ptr<EulIntToken>>() = std::make_shared<EulIntToken>(yytext);
    return yy::EulParser::token::INT;
}

([0-9]+([.][0-9]*)?|[.][0-9]+)(f[0-9]*)? {
    yylval->build<std::shared_ptr<EulFloatToken>>() = std::make_shared<EulFloatToken>(yytext);
    return yy::EulParser::token::FLOAT;
}


"if"	    return yy::EulParser::token::IF;
"else"	    return yy::EulParser::token::ELSE;
"else"[ \t]+"if"	    return yy::EulParser::token::ELSE_IF;
"while"		return yy::EulParser::token::WHILE;
"for"		return yy::EulParser::token::FOR;
"var"		return yy::EulParser::token::VAR;
"val"		return yy::EulParser::token::VAL;
"const"		return yy::EulParser::token::CONST;
"namespace"		return yy::EulParser::token::NAMESPACE;
"return"		return yy::EulParser::token::RETURN;

"true" {
    yylval->build<std::shared_ptr<EulBooleanToken>>() = std::make_shared<EulBooleanToken>(true);
    return yy::EulParser::token::BOOLEAN;
}

"false" {
    yylval->build<std::shared_ptr<EulBooleanToken>>() = std::make_shared<EulBooleanToken>(false);
    return yy::EulParser::token::BOOLEAN;
}


[a-zA-Z]{WORD_TAIL}* {
    yylval->build<std::shared_ptr<EulIdToken>>() = std::make_shared<EulIdToken>(yytext, yyleng, ctx->currentScope);
    return yy::EulParser::token::ID;
}


"+"		return yy::EulParser::token::PLUS;
"-"		return yy::EulParser::token::MINUS;
"~"		return yy::EulParser::token::TILDE;
"!"     return yy::EulParser::token::NOT;
"!="    return yy::EulParser::token::NOT_EQUALS;
"!=="   return yy::EulParser::token::NOT_SAME;
"@"     return yy::EulParser::token::AT;
"#"     return yy::EulParser::token::HASH;
"$"     return yy::EulParser::token::DOLLAR;
"%"     return yy::EulParser::token::PERCENT;
"%="    return yy::EulParser::token::ASSIGN_MOD;
"^"     return yy::EulParser::token::XOR;
"^="    return yy::EulParser::token::ASSIGN_XOR;
"&"     return yy::EulParser::token::BIN_AND;
"&&"    return yy::EulParser::token::AND;
"&="    return yy::EulParser::token::ASSIGN_AND;
"*"     return yy::EulParser::token::STAR;
"*="    return yy::EulParser::token::ASSIGN_STAR;
"("     return yy::EulParser::token::PARENTHESIS_OPEN;
")"     return yy::EulParser::token::PARENTHESIS_CLOSE;
"--"    return yy::EulParser::token::DECREASE;
"-="    return yy::EulParser::token::ASSIGN_MINUS;
"->"    return yy::EulParser::token::ARROW;
"="     return yy::EulParser::token::ASSIGN;
"=="    return yy::EulParser::token::EQUALS;
"==="   return yy::EulParser::token::SAME;
"++"    return yy::EulParser::token::INCREASE;
"+="    return yy::EulParser::token::ASSIGN_PLUS;
"["     return yy::EulParser::token::SQUARE_OPEN;
"]"     return yy::EulParser::token::SQUARE_CLOSE;
"{"     return yy::EulParser::token::CURLY_OPEN;
"}"     return yy::EulParser::token::CURLY_CLOSE;
"\\"    return yy::EulParser::token::BACKSLASH;
"|"     return yy::EulParser::token::BIN_OR;
"||"    return yy::EulParser::token::OR;
"|="    return yy::EulParser::token::ASSIGN_OR;
";"     return yy::EulParser::token::SEMICOLON;
":"     return yy::EulParser::token::COLON;
"/"     return yy::EulParser::token::SLASH;
"/="    return yy::EulParser::token::ASSIGN_DIV;
"?"     return yy::EulParser::token::QUESTION;
"."     return yy::EulParser::token::DOT;
","     return yy::EulParser::token::COMMA;
"<"     return yy::EulParser::token::LESS;
"<="    return yy::EulParser::token::LESS_EQUALS;
"<<"    return yy::EulParser::token::LSHIFT;
"<<="   return yy::EulParser::token::ASSIGN_LSHIFT;
">"     return yy::EulParser::token::MORE;
">="    return yy::EulParser::token::MORE_EQUALS;
">>"    return yy::EulParser::token::RSHIFT;
">>="   return yy::EulParser::token::ASSIGN_RSHIFT;
[\n]   {
    EulScanner::advanceLine(loc);
    return yy::EulParser::token::NL;
}


"\"" {
    std::shared_ptr<EulStringToken> ret = this->parseStringValue(ctx->compiler, loc);
    if (ctx->compiler->errors.size() != 0) return yy::EulParser::token::ERROR;

    yylval->build<std::shared_ptr<EulStringToken>>() = ret;
    return yy::EulParser::token::STRING;
}

"'\\" {
    std::shared_ptr<EulCharToken> ret = this->parseEscapedChar(ctx->compiler, loc);
    if (ctx->compiler->errors.size() != 0) return yy::EulParser::token::ERROR;

    yylval->build<std::shared_ptr<EulCharToken>>() = ret;
    return yy::EulParser::token::CHAR;
}

"'"{ANY_UNICODE}"'"	{
    std::shared_ptr<EulCharToken> ret = std::make_shared<EulCharToken>(yytext, yyleng, ctx->compiler);
    if (ctx->compiler->errors.size() != 0) return yy::EulParser::token::ERROR;

    yylval->build<std::shared_ptr<EulCharToken>>() = ret;
    return yy::EulParser::token::CHAR;
}

"/*"  {
    this->skipMultiLineComment(ctx->compiler, loc);
    if (ctx->compiler->errors.size() != 0) return yy::EulParser::token::ERROR;
}

"//"	{
    this->skipSingleLineComment(loc);
    if (ctx->compiler->errors.size() != 0) return yy::EulParser::token::ERROR;
    return yy::EulParser::token::NL;
}





<<EOF>> return yy::EulParser::token::END;

. {
  ctx->compiler->addError(EulErrorType::LEXER, "Unexpected character\n");
  return yy::EulParser::token::ERROR;
}

%%