#pragma once


//region LIFE CYCLE
//endregion


//region CORE FUNCTIONS
EulStatementType EulStatement::getStatementType() { return EulStatementType::UNKNOWN_STATEMENT; }
EulNodeType EulStatement::getNodeType() { return EulNodeType::STATEMENT; }

//endregion


//region CODE GENERATION
void EulStatement::performPreParsing(EulCodeGenContext* ctx) {
  //every performPreParsing within a block will be called BEFORE any generateStatement call.


  //By default, a statement does nothing during the pre-parsing
  //Subclasses that relate to symbol definition might want to do something in here.
}

void EulStatement::generateStatement(EulCodeGenContext* ctx) {
    throw EulError(EulErrorType::SEMANTIC, "EulStatement::generateStatement was called.");
}

void EulStatement::assertStatementReachable(EulCodeGenContext* ctx) {
    if (ctx->builder.GetInsertBlock()->getTerminator() == nullptr) return;
    throw EulError(EulErrorType::SEMANTIC, "Unreachable statement.");
}
//endregion


//region SERIALIZATION
//endregion
