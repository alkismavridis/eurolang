#include <map>
#include <iostream>
#include <fstream>


#include "EulCliParams.h"
#include "../../core/Compiler/EulError/EulError.h"



EulCliParams::EulCliParams(const int argc, const char **argv) {
    if (argc != 3) throw EulError(EulErrorType::PARAMS_ERROR, "Please provide input and output file.");

    //1. Setup input file
    std::string inputFileName = std::string(argv[1]);
    auto inFile = std::make_shared<std::ifstream>(inputFileName);
    if (!inFile->good()) throw EulError(EulErrorType::PARAMS_ERROR, "File not found: " + inputFileName);
    this->inputFiles[inputFileName] = inFile;

    //2. Setup output file
    this->outputFile.assign(argv[2]);
}
