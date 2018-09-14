#pragma once




class EulSourceFile {
    //region FIELDS
	public: std::string id;
    public: unsigned char isParsed;		/** indicates whether the compiler compiled this source file. */

    public: std::string nameSpace;
    //public: std::forward_list<EulImportStatement> imports;
    //public: std::forward_list<EulExportStatement> exports;
    public: std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>> statements; /** Can be null for empty files. */

    public: std::shared_ptr<EulScope> scope;
    //endregion




    //region LIFE CYCLE
    public: EulSourceFile(const std::string& id, std::shared_ptr<EulScope> globalScope);
    //endregion




    //region CODE GENERATOR
    public: void parseAST(EulCodeGenContext* ctx);
    public: void doASTPreParsing(EulCodeGenContext* ctx);
    //endregion
};

std::ostream& operator<<(std::ostream& out, EulSourceFile* file);
