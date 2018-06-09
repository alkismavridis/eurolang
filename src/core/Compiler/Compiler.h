#pragma once




class Compiler {
    //region FIELDS
    public: void (*onError)(Compiler* ths);

    /*
    Every time one file is being parsed.
    Once its done, we see if any imports are left and go on.
    If no imports are available, we stop parsing.
    */
    public:EulSourceFile* currentSource;

    public: std::string buffer; //this will serve the lexer.

    /*
    Here it comes: the program object
    */
    public: EulProgram program;


    //error related fields
    public: unsigned char errorCode;
    public: std::string errorMessage;
    //endregion




    //region LIFE CYCLE
    public: Compiler(void (*onError)(Compiler*));
    public: void reset(); //ths is just for unit testing purposes. It re-initializes the src field.
    //endregion



    //region API
    /*
      Looks in the Program for thr next source file and compiles it.
      It returns 1 if a file was compiled, 0 if no more files are present
    */
    public: void compile(const std::string& sourceName, std::istream *input);
    public: void compile(EulSourceFile *target, std::istream *input);
    //endregion




    //region ERROR RELATED ACTIONS
    public: void makeLexerError(const std::string& message);
    public: void makeSemanticError(const std::string& message);
    public: void makeFileNotFoundError(const std::string& message);
    public: void clearError();
    //endregion
};