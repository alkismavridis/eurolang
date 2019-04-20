#pragma once


//region LIFE CYCLE
//endregion


//region CORE FUNCTIONS
EulStatementType EulExportStatement::getStatementType() { return EulStatementType::EXPORT; }
//endregion


//region CODE GENERATION
//TODO
//endregion


//region SERIALIZATION
void EulExportStatement::toJson(std::ostream& out, int tabs) {
    out << "EulExportStatement" << std::endl;
}
//endregion
