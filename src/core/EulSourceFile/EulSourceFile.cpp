#include <string>
#include <forward_list>
#include <vector>
#include <map>
#include <iostream>

#include "../EulToken/EulTokenType.h"
#include "../EulToken/EulToken.h"
#include "../EulToken/EulIdToken.h"
#include "../EulAst/EulStatement/EulStatementType.h"
#include "../EulAst/EulAstType.h"
#include "../EulAst/EulAst.h"
#include "../EulAst/EulDeclaration/VarDeclaration.h"
#include "../EulAst/EulStatement/EulStatement.h"
#include "../EulAst/EulStatement/EulImportStatement.h"
#include "../EulAst/EulStatement/EulExportStatement.h"
#include "EulSourceFile.h"


//region LIFE CYCLE
EulSourceFile::EulSourceFile(const std::string& id) {
    this->isParsed = 0;
    this->id = id;
    this->statements = nullptr;
}

EulSourceFile::~EulSourceFile() {
    //1. deinit statements
    if (this->statements != nullptr) {
        for (auto stmt : *this->statements) delete stmt;
        delete this->statements;
    }
}
//endregion
