#pragma once

/**
    This is a wrapper object for an llvm::Type*
    The reason that we need a wrapper is because a Type may be not-yet-defined when it is requested.
    There will be no forward declarations in eurolang.
*/
class LateDefinedType : public EulType {
    //region FIELDS
    public: std::string name;
    //endregion



    //region LIFE CYCLE
    public: LateDefinedType(const std::string& name);
    public: virtual ~LateDefinedType();
    //endregion



    //region SERIALIZING
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion



    //region OVERRIDES
    public: bool isLateDeclared();
    //endregion
};