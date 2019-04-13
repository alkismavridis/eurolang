#pragma once

class VarDeclaration : public EulAst {
    //region FIELDS
    public: std::shared_ptr<EulSymbolNameNode> id;
    public: std::shared_ptr<EulType> varType;
    public: std::shared_ptr<EulNode> value; //either an expression or a IntToken, CharToken etc.
    //endregion



    //region LIFE CYCLE
    public: VarDeclaration(std::shared_ptr<EulSymbolNameNode> id, std::shared_ptr<EulType> varType, std::shared_ptr<EulNode>);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion




    //region OVERRIDES
    public: EulAstType getAstType();
    //endregion



    //region CODE GENERATOR
    /**
        returns the defined type, if it was explicitly set, or the
        default type of the declaration value, if no explicit type was set.
        The situation that neither is set (like var x;) is not yet implemented.
        When it is, probably a default value will be set.
    */
    public: std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam);
    //endregion
};
