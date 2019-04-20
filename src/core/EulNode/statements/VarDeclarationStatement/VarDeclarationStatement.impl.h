#pragma once


//region LIFE CYCLE
VarDeclarationStatement::VarDeclarationStatement(int varType, std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> declarations) {
    this->varType = varType;
    this->declarations = declarations;
}
//endregion



//region CORE FUNCTIONS
EulStatementType VarDeclarationStatement::getStatementType() { return EulStatementType::VAR_DECLARATION; }
//endregion



//region CODE GENERATION
void VarDeclarationStatement::generateStatement(EulCodeGenContext* ctx) {
    EulStatement::assertStatementReachable(ctx);

    for (auto decl : *this->declarations) {
        auto const varName = decl->id->name;

        //1. Get the variable. Throw an error if it does not exists
        auto const symbol = ctx->currentScope->get(varName);
        if (symbol == nullptr) {
            ctx->compiler->addError(EulError(EulErrorType::SEMANTIC, varName + " not found."));
            return;
        }

        //2. Store the value.
        //2a. Get the runtime value
        llvm::Value* runtimeValue;
        if (decl->value==nullptr) {
            //undefined value. Let llvm optimize what will happen
            runtimeValue = llvm::UndefValue::get(decl->varType->getLlvmType(ctx));
        }
        else {
            //we have a value. Lets compute it and store it.
            runtimeValue = decl->value->generateValue(ctx, EulCodeGenFlags_LOAD_VAR);
        }

        //2b. Set the symbol type
        symbol->varType = decl->getEulType(ctx, 0);

        //2b. cast the value to the declared type (or the type that the expression indicated, if no explicit type was specified)
        auto castedValue = decl->value==nullptr?
            runtimeValue:
            symbol->varType->castValue(runtimeValue, symbol->varType.get(), false, ctx);

        //2c. create the allocation and the store instruction
        auto allocInst = ctx->builder.CreateAlloca(symbol->varType->getLlvmType(ctx), nullptr, varName);
        ctx->builder.CreateStore(castedValue, allocInst);
        symbol->llvmValue = allocInst;
    }
}
//endregion



//region SERIALIZATION
void VarDeclarationStatement::toJson(std::ostream& out, int tabs) {
    out << "{" << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"type\":\"VarDeclarationStatement\"," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"varType\":" <<  this->varType << "," << std::endl;

    for (int i=tabs; i>=0; --i) out << "\t";
    out << "\"declarations\": TODO";
    //auto castedVector = std::static_pointer_cast<std::vector<std::shared_ptr<VarDeclaration>>>(this->declarations);
    //EulNode::toJson(out, *castedVector.get(), tabs+1);
    out << std::endl;

    for (int i=tabs-1; i>=0; --i) out << "\t";
    out << "}";
}
//endregion
