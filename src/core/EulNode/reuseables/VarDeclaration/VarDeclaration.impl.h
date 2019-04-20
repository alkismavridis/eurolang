#pragma once


//region LIFE CYCLE
VarDeclaration::VarDeclaration(std::shared_ptr<EulSymbolNameNode> id, std::shared_ptr<EulType> varType, std::shared_ptr<ValueNode> value) {
    this->id = id;
    this->varType = varType;
    this->value = value;
}
//endregion



//region CORE FUNCTIONS
EulNodeType VarDeclaration::getNodeType() { return EulNodeType::VAR_DECLATION_ITEM; }


/**
    returns the type declared type, if any.
    The type that can be extracted from the value otherwise.
*/
std::shared_ptr<EulType> VarDeclaration::getEulType(EulCodeGenContext* ctx, unsigned int someParam) {
    //1. If there is a declared type, return that
    if (this->varType != nullptr) return this->varType;

    //2. If there is no return type, but there is a value, return the "default" type for that value
    if (this->value != nullptr) return this->value->getEulType(ctx, 0);

    //3. TODO what happens if neither type not value is provided?
    throw EulError(EulErrorType::NOT_IMPLEMENTED, "NOT IMPLEMENTED: variable without initial value.");

}
//endregion



//region SERIALIZATION
void VarDeclaration::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\": \"VarDeclaration\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"id\":\"" <<  this->id->name << "\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->value!=nullptr) {
        out << "\"value\": ";
        this->value->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "\"value\": null" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->varType!=nullptr) {
        out << "\"varType\": ";
        this->varType->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "\"varType\": null" << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
