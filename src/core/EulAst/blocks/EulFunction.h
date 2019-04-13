#pragma once

/**
*/
class EulFunction : public EulAst {
    //region FIELDS
    public: std::shared_ptr<EulFunctionType> functionType;
    public: std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> parameters; //may be null if no parameters are present!
    public: std::shared_ptr<EulCodeBlock> block;
    //endregion



    //region MISC
    public: void toJson(std::ostream& out, int tabs);
    public: EulAstType getAstType();
    //endregion


    //region LIFE CYCLE
    public: EulFunction(
        std::shared_ptr<EulFunctionType> functionType,
        std::shared_ptr<std::vector<std::shared_ptr<VarDeclaration>>> parameters,
        std::shared_ptr<EulCodeBlock> block
    );
    //endregion
};
