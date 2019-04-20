#pragma once

class ValueNode : public EulNode {
  public: virtual llvm::Value* generateValue(EulCodeGenContext* ctx, unsigned int flags) = 0;
  public: virtual std::shared_ptr<EulType> getEulType(EulCodeGenContext* ctx, unsigned int someParam) = 0;
  public: virtual bool isSymbolId() = 0 ;
};
