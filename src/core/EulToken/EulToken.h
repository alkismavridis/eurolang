#pragma once


//region LANGUAGE DEFINITIONS
#define EUL_LANG_DEFAULT_INT_SIZE 4
#define EUL_LANG_DEFAULT_FLOAT_SIZE 8
//endregion



//region I AM SORRY FOR MYSELF AND ANY OTHER PROGRAMMER THAT HAS TO DO THIS POINTLESS THING
typedef struct EulToken EulToken;
typedef struct Compiler Compiler;
//endregion




//region INT VALUE
typedef struct {  //struct describing an integer literal, or a character literal
	unsigned long int value;
	unsigned char size; //in bytes
	char isUnsigned;
} IntTokenValue;

void EulToken_initInt(EulToken* this, char* text);
void EulToken_deinitInt(EulToken* this);
//endregion




//region FLOAT VALUE
typedef struct {  //struct describing a float literal
	double value;
	unsigned char size; //in bytes
} FloatTokenValue;

void EulToken_initFloat(EulToken* this, char* text);
void EulToken_deinitFloat(EulToken* this);
//endregion



//region CHAR VALUE
/** Char values use IntTokenValue as value type. */
void EulToken_initSimpleChar(EulToken* this, char* text, unsigned int len, Compiler *compiler);
void EulToken_initEscapedChar(EulToken* this, unsigned int value);
void EulToken_deinitChar(EulToken* this);
//endregion



//region STRING VALUE
void EulToken_initStringFromBuffer(EulToken* this, Compiler *compiler);
void EulToken_deinitString(EulToken* this);
//endregion



//region ID VALUE
/** Ids use simply a char* as value type. */
void EulToken_initId(EulToken* this, char* text, unsigned int len);
void EulToken_deinitId(EulToken* this);
//endregion




//region LIST VALUE
/** Ids use simply a EulNodeList* as value type. */
void EulToken_initList(EulToken* this);
void EulToken_initListWith(EulToken* this, EulToken* element);
void EulToken_deinitList(EulToken* this);
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
//endregion





//region ROOT TYPES
/**
    We define a class type.
    every token has a class.
    All tokens of the same type (for example, Ints) will have the same class.

    We do that to avoid big switch statements that would do stuff according to the token's type.
*/
typedef struct {
    void (*deinit)(EulToken*);
} EulTokenClass;


typedef union {
	//NOTE: keywords and operators do not have values.
	IntTokenValue* asInt;				//both INT and CHAR can use this
	FloatTokenValue* asFloat;
	char* asId;
	char* asString;

	//EulNodeList* asList;               //useful for plural bison stuff like statementS,
	//ParameterValue* asParam;
	EulSourceFile* asSourceFile;
	EulNodeList* asList;
	//...
	//...

} EulTokenValue;


typedef struct EulToken {
	EulTokenClass* class;
	EulTokenValue value;
} EulToken;
//endregion