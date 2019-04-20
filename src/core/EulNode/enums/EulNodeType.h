#pragma once

enum class EulNodeType {
    //region SPECIAL
    UNKNOWN,




    //region LEAF NODES
    INT,
    FLOAT,
    CHAR,
    STRING,
    BOOLEAN,
    ID,


    //region EXPRESSIONS
    EXPRESSION,



    //region STATEMENTS
    STATEMENT,




    //region REUSEABLES
    VAR_DECLATION_ITEM,
    CODE_BLOCK_TYPE,
    FUNC_DECLARATION_TYPE, //maybe move this so Expression category
    TYPE,


    //region DEPRECATED (R.I.P)
    AST,

};
