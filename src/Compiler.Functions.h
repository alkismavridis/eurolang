#pragma once
#include "core/ErrorTypes.h"
#include <string.h>
#include <stdlib.h>



//region LIFE CYCLE
void Compiler_init(Compiler* this, char* entryPoint, FILE* (*onGetFile)(char* path), void (*onError)(Compiler* this));
void Compiler_deinit(Compiler* this);
void Compiler_reset(Compiler* this, char* entryPoint); //this is just for unit testing purposes. It re-initalizes the src field.
//endregion



//region BUFFERING (for lexer)
void Compiler_addToStringBuffer(Compiler *this, char ch);
void Compiler_expandBuffer(Compiler *this);
//endregion


//region API
/*
  Looks in the Program for thr next source file and compiles it.
  It returns 1 if a file was compiled, 0 if no more files arepresent
*/
int Compiler_compileNextSource(Compiler *this);
//endregion



//region ERROR RELATED ACTIONS
void Compiler_makeLexerError(Compiler *this, char* message);
void Compiler_makeSemanticError(Compiler *this, char* message);
void Compiler_makeFileNotFoundError(Compiler *this, char* file);
void Compiler_clearError(Compiler *this);
//endregion
