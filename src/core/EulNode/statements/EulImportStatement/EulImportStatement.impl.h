#pragma once


//region LIFE CYCLE
//endregion


//region CORE FUNCTIONS
EulStatementType EulImportStatement::getStatementType() { return EulStatementType::IMPORT; }
//endregion


//region CODE GENERATION
//TODO
//endregion


//region SERIALIZATION
void EulImportStatement::toJson(std::ostream& out, int tabs) {
  out << "EulImportStatement TODO NOT IMPLEMENTED" << std::endl;
}
//endregion
