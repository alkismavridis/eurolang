#pragma once

struct CompileOptions {
    const std::string sourceFileName;

    CompileOptions(const std::string& sourceFileName) :
        sourceFileName(sourceFileName) {}
};
