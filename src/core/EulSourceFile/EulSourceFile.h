#pragma once




class EulSourceFile {
    //region FIELDS
	public: std::string id;
    public: unsigned char isParsed;		/** indicates whether the compiler compiled this source file. */

    public: std::string nameSpace;
    //public: std::forward_list<EulImportStatement> imports;
    //public: std::forward_list<EulExportStatement> exports;
    //public: std::map<std::string, VarDeclaration*> symbols;
    public: std::vector<EulStatement*>* statements; /** Can be null for empty files. */
    //endregion




    //region LIFE CYCLE
    public: EulSourceFile(const std::string& id);
    public: ~EulSourceFile();
    //endregion
};
