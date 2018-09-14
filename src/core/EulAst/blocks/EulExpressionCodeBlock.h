#pragma once

/**
    A code block paired with an expression.
    This can be used for if blocks, else if blocks, while blocks etc.
*/
class EulExpressionCodeBlock {
    //region FIELDS
    public: std::shared_ptr<EulToken> expression;
    public: std::shared_ptr<EulCodeBlock> block;
    //endregion



    //region LIFE CYCLE
    public: EulExpressionCodeBlock(std::shared_ptr<EulToken> expression, std::shared_ptr<EulCodeBlock> block);
    //endregion
};