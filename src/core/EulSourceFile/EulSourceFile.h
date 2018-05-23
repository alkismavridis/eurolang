#pragma once


//region SOURCE
typedef struct {
	char* id;
    char isParsed;		//indicates whether the compiler compiled this source file.

	char* nameSpace;
	EulNodeList imports; //not yet implemented
	EulNodeList exports; //not yet implemented
	EulNodeList symbols; //not yet implemented
	EulNodeList statements;  //possible elements types on this list:
} EulSourceFile;




//region LIFE CYCLE
void EulSourceFile_init(EulToken* this, char* entryPoint);
void EulSourceFile_deinit(EulToken* this);
//endregion
