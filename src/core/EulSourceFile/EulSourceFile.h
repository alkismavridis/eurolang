#pragma once




class EulSourceFile {
    //region FIELDS
	public: std::string id;
    public: unsigned char isParsed;		/** indicates whether the compiler compiled this source file. */

    public: std::string nameSpace;
    public: std::forward_list<EulImportStatement> imports;
    public: std::forward_list<EulExportStatement> exports;
    public: std::map<std::string, EulSymbol*> symbols;
    public: std::forward_list<EulStatement> statements;
    //endregion




    //region LIFE CYCLE
    public: EulSourceFile(const std::string& id);
    public: ~EulSourceFile();
    //endregion
};
