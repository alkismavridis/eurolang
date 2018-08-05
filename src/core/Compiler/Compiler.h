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

    /** *Here we will store the error object, if any happens. */
    public: std::vector<EulError*> errors;
    //endregion




    //region LIFE CYCLE
    public: Compiler(void (*onError)(Compiler*));
    public: ~Compiler();
    public: void reset(); //ths is just for unit testing purposes. It re-initializes the src field.
    //endregion



    //region API
    /*
      Looks in the Program for thr next source file and compiles it.
      It returns 1 if a file was compiled, 0 if no more files are present
    */
    public: void compile(const std::string& sourceName, std::istream *input);
    public: void compile(EulSourceFile *target, std::istream *input);
    public: void produceOutput(const std::string& outputFileName);
    //endregion




    //region ERROR RELATED ACTIONS
    public: void addError(const EulError& error);
    public: void addError(int errorType, const std::string& message);
    public: void clearErrors();
    //endregion
};