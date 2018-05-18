#pragma once

#include <string.h>
#define YY_NULL 0 //TODO find a way to remove that
#define EUL_LANG_DEFAULT_INT_SIZE 4
#define EUL_LANG_DEFAULT_FLOAT_SIZE 8



//region NODE
void EulNode_push(EulNode* this, EulToken* value);
//void EulNode_init(EulToken* this, EulToken* child);
//void EulNode_deinit(EulToken* this);
//endregion




//region NODE LIST
void EulNodeList_init(EulNodeList* this);
void EulNodeList_push(EulNodeList* this, EulToken* value);
int EulNodeList_length(EulNodeList* this);
void EulNodeList_deinitAllNodes(EulNodeList* this);
//endregion




//region TERMINALS
void EulToken_deinit(EulToken* this); //entry point for deinit functions. It will also call the appropriate deinit for the value.
EulToken* EulToken_initInt(EulToken* this, char* text);
EulToken* EulToken_newFloat(char* text);
EulToken* EulToken_newId(char* text, unsigned int len);
EulToken* EulToken_newSimpleChar(char* text, unsigned int len, Compiler *compiler);
//endregion




//region PROGRAM VALUE
void EulProgram_init(EulProgram* this, char* entryPoint);
void EulProgram_deinit(EulProgram* this);


/**
  returns a Token of type EulTokenType_SOURCE_FILE, associated with the given id.
  Please note that id is unique on the program, and thus, this function will
  calling it multiple times with the same id will always return the same sourceFile.

  Also note that, once a source file is appended on the program, it will be accessible
  everywhere in the compiler. This can help us transmit signals between source files.

  If the createIfNotExists flag is set and the file with the given id is not found,
  a new token will be created and returned.
  Otherwise, NULL will be returned.

*/
EulToken* EulProgram_getSource(EulProgram* this, char* id, char createIfNotExists);

/**
  Will be probably called by the Compiler object every time it needs to get the next source file.
  returns a token with type EulTokenType_SOURCE_FILE,
          NULL if it not in file list.
  Please note that only parsed files go to this list.
  Files that are founded to be "imported", but not yet parsed, are stored int a different list.
*/
EulToken* EulProgram_nextPendingSource(EulProgram* this);
//endregion




//region SOURCE FILE
void EulSourceFile_init(EulSourceFile* this, char* entryPoint);
void EulSourceFile_deinit(EulSourceFile* this);
//TODO
//endregion
