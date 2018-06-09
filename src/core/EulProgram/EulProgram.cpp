#include <string>
#include <forward_list>
#include <map>
#include <iostream>
#include "../../constants/Constants.h"

#include "../EulAst/EulStatement/EulStatementType.h"
#include "../EulAst/EulAstType.h"
#include "../EulAst/EulStatement/EulStatement.h"
#include "../EulAst/EulStatement/EulImportStatement.h"
#include "../EulAst/EulStatement/EulExportStatement.h"
#include "../EulAst/EulSymbol.h"


#include "../EulSourceFile/EulSourceFile.h"
#include "EulProgram.h"


//region LIFE CYCLE
EulProgram::EulProgram() {}
EulProgram::~EulProgram() {}
//endregion




EulSourceFile* EulProgram::getSource(const std::string& id, unsigned char createIfNotExists) {
    //try finding the file
    auto entry = this->sources.find(id);
    if(entry != this->sources.end()) return entry->second;

    //we did not find the token. What we should now do, depends on createIfNotExists.
    if (!createIfNotExists) return 0;

    //we create a token, add it on our list, and return it.
    EulSourceFile* ret = new EulSourceFile(id);
    this->sources[id] = ret;
    return ret;
}


/**
  Will be probably called by the Compiler object every time it needs to get the next source file.
  returns null if all files are parsed.
*/
EulSourceFile* EulProgram::nextPendingSource() {
    for (auto const& e : this->sources) {
        if ( !e.second->isParsed ) return e.second;
    }

    //all files are parsed. return null.
    return 0;
}
//endregion