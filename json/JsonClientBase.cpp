#include "JsonClientBase.h"

JsonClientBase::JsonClientBase()
    : parent(NULL)
{
}

JsonClientBase::JsonClientBase(JsonClientBase *parent_, string target_)
    : parent(parent_), target(target_)
{
}
        
void JsonClientBase::set(JsonClientBase *parent_, string target_)
{
    parent = parent_;
    target = target_;
}

Json::Value JsonClientBase::invoke(const string &command, const Json::Value &parameters)
{
    return doInvoke(buildRequest(command, parameters));
}

Json::Value JsonClientBase::buildRequest(const string &command, const Json::Value &parameters)
{
    Json::Value request;
    request[0] = command;
    request[1] = parameters;

    return request;
}

Json::Value JsonClientBase::doInvoke(const Json::Value &request)
{
    if (parent == this) {
        throw string("Trying auto-parent");
    }

    if (parent == NULL) {
        throw string("JsonClient is NULL");
    }

    if (target == "") {
        return parent->doInvoke(request);
    } else {
        Json::Value parameters;
        parameters[0] = target;
        parameters[1] = request;

        return parent->doInvoke(buildRequest("sub", parameters));
    }
}

JsonClientBase &JsonClientBase::operator[](const string &target)
{
    return to(target);
}

        
JsonClientBase &JsonClientBase::to(const string &target)
{
    if (targets.find(target) == targets.end()) {
        targets[target].set(this, target);
    }

    return targets[target];
}
