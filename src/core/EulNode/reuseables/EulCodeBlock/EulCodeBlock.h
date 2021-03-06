#pragma once


class EulCodeBlock : public EulNode {
    //region FIELDS
    public: std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>> statements;
    public: std::shared_ptr<EulScope> scope;
    //endregion



    //region LIFE CYCLE
    public: EulCodeBlock(std::shared_ptr<std::vector<std::shared_ptr<EulStatement>>> statements, std::shared_ptr<EulScope> scope);
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion

    public: virtual EulNodeType getNodeType();
    public: void generateStatements(EulCodeGenContext* ctx);
};
