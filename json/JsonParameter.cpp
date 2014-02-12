#include "JsonParameter.h"

using std::string;

JsonParameter::JsonParameter(string name_) 
    : name(name_)
{
}

string JsonParameter::getName()
{
    return name;
}

bool JsonParameter::canDeserialize(const Json::Value &json)
{
    (void)json;
    return true;
}

JsonParameter *JsonParameter::setAttribute(std::string name, std::string value)
{
    attributes[name] = value;

    return this;
}

Json::Value JsonParameter::getAttributes()
{
    return attributes;
}
