#pragma once


//region LIFE CYCLE
EulArrayAccessExp::EulArrayAccessExp(std::shared_ptr<ValueNode> obj, std::shared_ptr<ValueNode> index) {
    this->obj = obj;
    this->index = index;
}
//endregion



//region CORE FUNCTIONS
EulExpressionType EulArrayAccessExp::getExpressionType() { return EulExpressionType::ARRAY_ACCESS; }
//endregion




//region CODE GENERATION
llvm::Value* EulArrayAccessExp::generateValue(EulCodeGenContext* ctx, unsigned int flags) {
    std::cout << "EulArrayAccessExp::generateValue TODO NOT IMPLEMENTED" << std::endl;
    return nullptr;
}
//endregion



//region SERIALIZATION
void EulArrayAccessExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulArrayAccessExp\"," << std::endl;


    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"obj\":";
    this->obj->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"index\":";
    this->index->toJson(out, tabs+1);
    out << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
