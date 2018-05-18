#pragma once
#include <stdio.h>


//region FIELDS
typedef struct Compiler Compiler;
typedef struct Compiler {
  /* callback for asking the new file. We put this as a callback for easier testability (mocking).  */
  FILE* (*onGetFile)(char* path);
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
