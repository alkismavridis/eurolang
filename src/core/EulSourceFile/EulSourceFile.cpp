#include <string>
#include <forward_list>
#include <map>

#include "../EulAst/EulStatement/EulStatementType.h"
#include "../EulAst/EulAstType.h"
#include "../EulAst/EulStatement/EulStatement.h"
#include "../EulAst/EulStatement/EulImportStatement.h"
#include "../EulAst/EulStatement/EulExportStatement.h"
#include "../EulAst/EulSymbol.h"
#include "EulSourceFile.h"


//region LIFE CYCLE
EulSourceFile::EulSourceFile(const std::string& id) {
    this->isParsed = 0;
    this->id = id;
}

EulSourceFile::~EulSourceFile() {
}
//endregion
