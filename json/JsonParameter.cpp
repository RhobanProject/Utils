#include "JsonParameter.h"

JsonParameter::JsonParameter(string name_, string description_) 
    : name(name_), description(description_)
{
}

string JsonParameter::getName()
{
    return name;
}

string JsonParameter::getDescription()
{
    return description;
}

bool JsonParameter::canDeserialize(const Json::Value &json)
{
    (void)json;
    return true;
}
