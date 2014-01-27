#include "JsonClientProxy.h"

JsonClientProxy::JsonClientProxy()
{
}

JsonClientProxy::JsonClientProxy(JsonClientBase *parent_, string target_)
: parent(parent_), target(target_)
{
}

Json::Value JsonClientProxy::invoke(const Json::Value &request)
{
    Json::Value parameters;
    parameters[0] = target;
    parameters[1] = request;

    return parent->invoke(buildRequest("sub", parameters));
}

JsonClientProxy JsonClientProxy::operator[](const string &target)
{
    return JsonClientProxy(this, target);
}

