#pragma once

typedef struct EulToken EulToken;

typedef struct EulNode EulNode;
typedef struct EulNode {
	EulNode *next;
	EulToken *value;
} EulNode;

typedef struct EulNodeList EulNodeList;
typedef struct EulNodeList {
	EulNode *first;
	EulNode *last;
} EulNodeList;


//region TERMINALS
typedef struct {  //struct describing an integer literal, or a character literal
	unsigned long int value;
	unsigned char size; //in bytes
	char isUnsigned;
} IntTokenValue;

typedef struct {  //struct describing a float literal
	double value;
	unsigned char size; //in bytes
} FloatTokenValue;
//endregion




//region NODE VALUES
/**
	This represents a key:type:value group.
	It can be used for function param definitions, variable declarations, etc.
*/
typedef struct {
    //TODO a lot of stuff will go here
    char* varName;
} EulType;


typedef struct {
	char* varName;
	EulType type; //TODO here a real "EulType" will go here
	EulToken* valueToken;	//can be also null...
} ParameterValue;




/**
	type:EulTokenType_PROGRAM
	This represents the whole program, that includes many parsed source files,
	and a stack of files that were requested as "imported", but were not yet parsed.
*/
typedef struct {
	EulToken* entryPoint;	//a token of type EulTokenType_SOURCE_FILE than indicates where the program starts.
	EulNodeList sources;	//includes only EulTokenType_SOURCE_FILE tokens. Both parsed and to-be-parsed file go here.
} EulProgram;


//type:EulTokenType_SOURCE_FILE
typedef struct {
	char* id;
	char* nameSpace;
	char isParsed;		//indicates whether the compiler compiled this source file.
	EulNodeList imports; //not yet implemented
	EulNodeList exports; //not yet implemented
	EulNodeList symbols; //not yet implemented
	EulNodeList statements;  //possible elements types on this list:
} EulSourceFile;
//endregion





//region ROOT TYPES
typedef union {
	//NOTE: keywords and operators do not have values.
	IntTokenValue asInt;				//both INT and CHAR can use this
	FloatTokenValue asFloat;
	char* asId;
	char* asString;
	//EulNode asNode;
	//IfStatementValue
	ParameterValue asParam;
	EulProgram* asProgram;
	EulSourceFile* asSourceFile;
	//...
	//...

} EulTokenValue;


typedef struct EulToken {
	unsigned int type;
	EulTokenValue value;
} EulToken;
//endregion
