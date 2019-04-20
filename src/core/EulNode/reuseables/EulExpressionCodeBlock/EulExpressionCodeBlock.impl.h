#pragma once

EulExpressionCodeBlock::EulExpressionCodeBlock(std::shared_ptr<ValueNode> expression, std::shared_ptr<EulCodeBlock> block) {
    this->block = block;
    this->expression = expression;
}
