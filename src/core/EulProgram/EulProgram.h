#pragma once



//region WHY?
typedef struct EulToken EulToken;
//endregion




//region FIELDS
/**
	type:EulTokenType_PROGRAM
	This represents the whole program, that includes many parsed source files,
	and a stack of files that were requested as "imported", but were not yet parsed.
*/
typedef struct {
	EulToken* entryPoint;	//a token of type EulTokenType_SOURCE_FILE than indicates where the program starts.
	EulNodeList sources;	//includes only EulTokenType_SOURCE_FILE tokens. Both parsed and to-be-parsed file go here.
} EulProgram;
//endregion




//region LIFE CYCLE
void EulProgram_init(EulProgram* this);
void EulProgram_deinit(EulProgram* this);
//endregion



//region GETTERS
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