#pragma once

/**
    EulExpStatement stands for Eul Expression Statement.
    This is a statement that is made of one Expression, like a function call or an assignment.
*/
class EulWhileStatement : public EulStatement {
    //region FIELDS
    public: EulExpressionCodeBlock expBlock;
    //endregion



    //region LIFE CYCLE
    public: EulWhileStatement(std::shared_ptr<ValueNode> condition, std::shared_ptr<EulCodeBlock> codeBlock);
    //endregion



    //region MISC
    public: virtual void toJson(std::ostream& out, int tabs);
    public: EulStatementType getStatementType();
    //endregion


    //region CODE GENERATION
    public: void generateStatement(EulCodeGenContext* ctx);
    //endregion
};
