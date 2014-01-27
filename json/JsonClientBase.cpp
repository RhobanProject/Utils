#include "JsonClientBase.h"

Json::Value JsonClientBase::invoke(const string &command, const Json::Value &parameters)
{
    return invoke(buildRequest(command, parameters));
}

Json::Value JsonClientBase::buildRequest(const string &command, const Json::Value &parameters)
{
    Json::Value request;
    request[0] = command;
    request[1] = parameters;

    return request;
}
