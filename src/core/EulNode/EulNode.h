#pragma once

/**
    This is the base class of all tokens. It only provides a getNodeType() method, which will determine if this token
    is an Operator token, an Integer token and so on.
*/
class EulNode {
    public: virtual ~EulNode();


    //region SERIALIZING
    public: virtual EulNodeType getNodeType();
    public: virtual void toJson(std::ostream& out, int tabs);
    //endregion


    public: static void toJsonArray(std::ostream& out, const std::vector<EulNode*>* tokens, int tabs);
    public: static void toJsonArray(std::ostream& out, const std::vector<std::shared_ptr<EulNode>> tokens, int tabs);
};

std::ostream& operator<<(std::ostream& os, EulNode* tok);
