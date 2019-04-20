#pragma once

class EulIfStatement : public EulStatement {
    //region FIELDS
    public: EulExpressionCodeBlock ifSection;
    public: std::shared_ptr<std::vector<std::shared_ptr<EulExpressionCodeBlock>>> elseIfs; //may be null!
    public: std::shared_ptr<EulCodeBlock> elseSection;                //may be null!
    //endregion



    //region LIFE CYCLE
    public: EulIfStatement(std::shared_ptr<ValueNode> condition, std::shared_ptr<EulCodeBlock> ifBlock); //single if

    public: EulIfStatement( //if else
        std::shared_ptr<ValueNode> condition,
        std::shared_ptr<EulCodeBlock> ifBlock,
        std::shared_ptr<EulCodeBlock> elseSection
    );

    public: EulIfStatement(  //if else-ifs else
        std::shared_ptr<ValueNode> condition,
        std::shared_ptr<EulCodeBlock> ifBlock,
        std::shared_ptr<std::vector<std::shared_ptr<EulExpressionCodeBlock>>> elseIfs,
        std::shared_ptr<EulCodeBlock> elseSection
    );
    //endregion



    //region MISC
    public: virtual void toJson(std::ostream& out, int tabs);
    public: EulStatementType getStatementType();
    //endregion


    //region CODE GENERATION
    /**
        returns the block to jump in case that the if condition fails.
        This can be the first else-if condition, the else block if no else-ifs are present,
        or the endBlock if neither else-ifs nor else exist.
    */
    public: llvm::BasicBlock* getFailingIfBLock(llvm::Function* currentFunction, llvm::BasicBlock* endBlock, EulCodeGenContext* ctx);
    public: void generateConditionBlock(EulExpressionCodeBlock* block, llvm::BasicBlock* blockOnFail, llvm::BasicBlock* endBlock, llvm::Function* currentFunction, EulCodeGenContext* ctx);
    public: void generateStatement(EulCodeGenContext* ctx);
    //endregion
};
