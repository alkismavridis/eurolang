#pragma once

class EulCliParams {
    //region FIELDS
    public: std::map<std::string, std::shared_ptr<std::istream>> inputFiles;
    public: std::string outputFile;
    //endregion



    //region UTIL FUNCTIONS
    //endregion




    //region LIFE CYCLE
    public: EulCliParams(const int argc, const char **argv);
    //endregion
};