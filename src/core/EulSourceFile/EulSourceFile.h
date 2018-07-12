#pragma once




class EulSourceFile {
    //region FIELDS
	public: std::string id;
    public: unsigned char isParsed;		/** indicates whether the compiler compiled this source file. */

    public: std::string nameSpace;
    //public: std::forward_list<EulImportStatement> imports;
    //public: std::forward_list<EulExportStatement> exports;
    public: std::map<std::string, EulSymbol*> symbols;              /** NOTE: contents of symbols map are NOT destructed. */
    public: std::vector<EulStatement*>* statements; /** Can be null for empty files. */

    public: std::map<std::string, EulSymbol*>* globalDeclarations; /** NOTE: globalDeclarations is NOT destructed. */
    //endregion




    //region LIFE CYCLE
    public: EulSourceFile(const std::string& id, std::map<std::string, EulSymbol*>* globalDeclarations);
    public: ~EulSourceFile();
    //endregion



    //region GETTERS
    public: EulSymbol* getSymbol(const std::string& name);
    //endregion

};

std::ostream& operator<<(std::ostream& out, EulSourceFile* file);
