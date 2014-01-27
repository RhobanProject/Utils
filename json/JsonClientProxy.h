#ifndef _JSON_CLIENT_PROXY_H
#define _JSON_CLIENT_PROXY_H

#include "JsonClientBase.h"

class JsonClientProxy : public JsonClientBase
{
    public:
        JsonClientProxy();
        JsonClientProxy(JsonClientBase *parent_, string target_);

        using JsonClientBase::invoke;

        virtual Json::Value invoke(const Json::Value &request);
        JsonClientProxy operator[](const string &target);

    protected:
        JsonClientBase *parent;
        string target;
};

#endif
