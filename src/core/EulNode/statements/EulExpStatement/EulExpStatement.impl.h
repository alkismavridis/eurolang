#pragma once


//region LIFE CYCLE
EulExpStatement::EulExpStatement(std::shared_ptr<ValueNode> exp) {
    this->exp = exp;
}
//endregion




//region CORE FUNCTIONS
EulStatementType EulExpStatement::getStatementType() { return EulStatementType::EXPRESSION_STATEMENT; }
//endregion



//region CODE GENERATION
void EulExpStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);
    exp->generateValue(ctx, EulCodeGenFlags_NONE);
}
//endregion



//region SERIALIZATION
void EulExpStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulExpStatement\"," << std::endl;


    //print value
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\": ";
    if (this->exp != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->exp->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "null" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

//endregion
