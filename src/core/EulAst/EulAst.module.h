/** On this file, we will implement all methods from every header file on this "package". */



//region BASE CLASS
EulAstType EulAst::getAstType() { return NO_TYPE; }
EulTokenType EulAst::getType() { return AST; }
//endregion


//region VAR DECLARATION
VarDeclaration::VarDeclaration(EulIdToken* id, EulType* varType, EulToken* value) {
    this->id = id;
    this->varType = varType;
    this->value = value;
}

VarDeclaration::~VarDeclaration() {
    delete this->id;
    if (this->varType != nullptr) delete this->varType;
    if (this->value != nullptr) delete this->value;
}

EulAstType VarDeclaration::getAstType() { return PARAM_DECLARATION; }

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



//region STATEMENT BASE
EulStatementType EulStatement::getStatementType() { return UNKNOWN_STATEMENT; }
EulAstType EulStatement::getAstType() { return STATEMENT; }
//endregion



//region IMPORT STATEMENT
EulStatementType EulImportStatement::getStatementType() { return IMPORT; }

void EulImportStatement::toJson(std::ostream& out, int tabs) {
    out << "Unknown token" << std::endl;
}
//endregion



//region EXPORT STATEMENT
EulStatementType EulExportStatement::getStatementType() { return EXPORT; }

void EulExportStatement::toJson(std::ostream& out, int tabs) {
    out << "EulExportStatement" << std::endl;
}
//endregion



//region VARIABLE DECLARATION STATEMENT
VarDeclarationStatement::VarDeclarationStatement(int varType, std::vector<VarDeclaration*>* declarations) {
    this->varType = varType;
    this->declarations = declarations;
}

VarDeclarationStatement::~VarDeclarationStatement() {
    if (this->declarations != nullptr) {
        for (auto d : *this->declarations) delete d;
        delete this->declarations;
    }
}

EulStatementType VarDeclarationStatement::getStatementType() { return VAR_DECLARATION; }

void VarDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"VarDeclarationStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\":" <<  this->varType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"declarations\": ";
    EulToken::toJson(out, (std::vector<EulToken*>*)this->declarations, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion




//region EXPRESSION BASE
EulAstType EulExpression::getAstType() { return EXPRESSION; }
EulExpressionType EulExpression::getExpressionType() { return UNKNOWN_EXP; }
//endregion



//region PREFIX EXPRESSION
EulPrefixExp::EulPrefixExp(int operatorType, EulToken* exp) {
    this->exp = exp;
    this->operatorType = operatorType;
}

EulPrefixExp::~EulPrefixExp() {
    delete this->exp;
}

void EulPrefixExp::toJson(std::ostream& out, int tabs) {
   out << "{" << std::endl;
   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"type\":\"EulPrefixExp\"," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"operatorType\":" << this->operatorType << "," << std::endl;

   for (int i=tabs; i>=0; --i) out << "\t";
   out << "\"exp\":";
   this->exp->toJson(out, tabs+1);
   out << std::endl;

   for (int i=tabs-1; i>=0; --i) out << "\t";
   out << "}";
}

EulExpressionType EulPrefixExp::getExpressionType() { return PREFIX_EXP; }
//endregion




//region INFIX EXPRESSION
EulInfixExp::EulInfixExp(EulToken* left, int operatorType, EulToken* right) {
    this->left = left;
    this->operatorType = operatorType;
    this->right = right;
}

EulInfixExp::~EulInfixExp() {
    delete this->left;
    delete this->right;
}

void EulInfixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulInfixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"left\":";
    this->left->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"operatorType\":" << this->operatorType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"right\":";
    this->right->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulInfixExp::getExpressionType() { return INFIX_EXP; }
//endregion



//region SUFFIX EXPRESSION
EulSuffixExp::EulSuffixExp(EulToken* exp, int operatorType) {
    this->exp = exp;
    this->operatorType = operatorType;
}

EulSuffixExp::~EulSuffixExp() {
    delete this->exp;
}

void EulSuffixExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSuffixExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"exp\":";
    this->exp->toJson(out, tabs+1);
    out << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"operatorType\":" << this->operatorType << "," << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulSuffixExp::getExpressionType() { return SUFFIX_EXP; }
//endregion



//region TOKEN EXPRESSION
EulTokenExp::EulTokenExp(EulToken* token) { this->token = token; }
EulTokenExp::~EulTokenExp() { delete this->token; }

void EulTokenExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulTokenExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"token\":";
    this->token->toJson(out, tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulTokenExp::getExpressionType() { return TOKEN; }
//endregion




//region FUNCTION CALL EXPRESSION
EulFunctionCallExp::EulFunctionCallExp(EulToken* func, std::vector<EulToken*>* params) {
    this->func = func;
    this->params = params;
}

EulFunctionCallExp::~EulFunctionCallExp() {
    if (this->params != nullptr) {
        for (auto p : *this->params) delete p;
        delete this->params;
    }

    delete this->func;
}

void EulFunctionCallExp::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulFunctionCallExp\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"func\":";
    this->func->toJson(out, tabs+1);
    out << std::endl;


    //print parameters
    for (int i=tabs; i>=0; --i) out << "\t";
    if (this->params == nullptr) out << "\"params\": null" << std::endl;
    else {
        out << "\"params\": [" << std::endl;

        //print one parameter in each loop step
        for (auto p : *this->params) {
            for (int i=tabs+1; i>=0; --i) out << "\t";
            p->toJson(out, tabs+2);
            out << "," << std::endl; //TODO last entry should be without comma
        }
        for (int i=tabs; i>=0; --i) out << "\t";
        out << "]" << std::endl;
    }

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulExpressionType EulFunctionCallExp::getExpressionType() { return FUNCTION_CALL; }
//endregion




//region FUNCTION CALL EXPRESSION
EulArrayAccessExp::EulArrayAccessExp(EulToken* obj, EulToken* index) {
    this->obj = obj;
    this->index = index;
}

EulArrayAccessExp::~EulArrayAccessExp() {
    delete this->obj;
    delete this->index;
}

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

EulExpressionType EulArrayAccessExp::getExpressionType() { return ARRAY_ACCESS; }
//endregion



//region EUL TYPE
EulType::EulType(const std::string& name) {
    this->name = name;
}

EulType::~EulType() {}

void EulType::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulType\"," << std::endl;


    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"name\":\"" << this->name << "\"" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulAstType EulType::getAstType() { return EUL_TYPE; }
//endregion




//region EUL SYMBOL
EulSymbol::EulSymbol(int changeType, const std::string& name, EulType* varType, EulToken* value) {
    this->changeType = changeType;
    this->name = name;
    this->varType = varType;
    this->value = value;
}

EulSymbol::~EulSymbol() {
    if (this->varType!=nullptr) delete this->varType;
    if (this->value!=nullptr) delete this->value;
}

void EulSymbol::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"EulSymbol\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"changeType\": " << this->changeType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"name\":\"" << this->name << "\"," << std::endl;

    //print var type
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\": ";
    if (this->varType != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->varType->toJson(out, tabs+1);
        out << "," << std::endl;
    }
    else out << "null," << std::endl;

    //print value
    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"value\": ";
    if (this->value != nullptr) {
        for (int i=tabs; i>=0; --i) out << "\t";
        this->value->toJson(out, tabs+1);
        out << std::endl;
    }
    else out << "null" << std::endl;

    //close json object
    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}

EulAstType EulSymbol::getAstType() { return EUL_SYMBOL; }
//endregion



//region EUL EXPRESSION STATEMENT
EulExpStatement::EulExpStatement(EulToken* exp) {
    this->exp = exp;
}

EulExpStatement::~EulExpStatement() {
    if (this->exp != nullptr) delete this->exp;
}

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

EulStatementType EulExpStatement::getStatementType() { return EulStatementType::EXPRESSION_STATEMENT; }
//endregion
