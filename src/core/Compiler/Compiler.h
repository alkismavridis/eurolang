#pragma once
#include <stdio.h>


//region FIELDS
typedef struct Compiler Compiler;
typedef struct Compiler {
  void (*onError)(Compiler* this);

  /*
    Every time one file is being parsed.
    Once its done, we see if any imports are left and go on.
    If no imports are available, we stop parsing.
  */
  EulSourceFile* currentSource;
  void* scanner;

  //buffering
	unsigned int stringBufferIndex; //for buffering
	unsigned int stringBufferLength;
	char* stringBuffer;

  /*
    Here it comes: the program object
  */
  EulProgram program;


  //error related fields
  unsigned char errorCode;
  char* errorMessage;
} Compiler;
//endregion




//region LIFE CYCLE
void Compiler_init(Compiler* this, void (*onError)(Compiler* this));
void Compiler_deinit(Compiler* this);
void Compiler_reset(Compiler* this); //this is just for unit testing purposes. It re-initializes the src field.
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
void Compiler_compile(Compiler *this, EulSourceFile *target, FILE* file);
//endregion




//region ERROR RELATED ACTIONS
void Compiler_makeLexerError(Compiler *this, char* message);
void Compiler_makeSemanticError(Compiler *this, char* message);
void Compiler_makeFileNotFoundError(Compiler *this, char* file);
void Compiler_clearError(Compiler *this);
//endregion
