#include <iostream>
#include "JsonParameters.h"

using std::vector;
using std::string;
using std::map;

JsonParameters::~JsonParameters()
{
    {
        vector<JsonParameter*>::iterator it;
        for (it=outputs.begin(); it!=outputs.end(); it++) {
            delete *it;
        }
    }
    {
        map<string, JsonParameter*>::iterator it;
        for (it=parameters.begin(); it!=parameters.end(); it++) {
            delete it->second;
        }
    }
}

vector<JsonParameter*> JsonParameters::getOutputs()
{
    return outputs;
}

vector<JsonParameter*> JsonParameters::getParameters()
{
    vector<JsonParameter*> allParameters;
    map<string, JsonParameter*>::iterator it;

    for (it=parameters.begin(); it!=parameters.end(); it++) {
        allParameters.push_back(it->second);
    }

    return allParameters;
}

bool JsonParameters::hasParameter(string name)
{
    return (parameters.find(name) != parameters.end());
}

JsonParameter *JsonParameters::getParameter(string name)
{
    return (hasParameter(name) ? parameters[name] : NULL);
}
        
void JsonParameters::importParameters(Json::Value parametersImport)
{
    if (parametersImport.isObject()) {
        Json::Value::Members members = parametersImport.getMemberNames();
        Json::Value::Members::iterator it;

        for (it=members.begin(); it!=members.end(); it++) {
            string name = *it;
            JsonParameter *parameter = getParameter(name);
            if (parameter != NULL) {
                if (parameter->canDeserialize(parametersImport[name])) {
                    parameter->deserialize(parametersImport[name]);
                } else {
                    std::cerr << "Can't load parameter " << name << std::endl;
                }
            } else {
                std::cerr << "Non-existent parameter: " << name << std::endl;
            }
        }
    } else {
        if (!parametersImport.isNull()) {
            std::cerr << "Parameters values should be an object" << std::endl;
        }
    }
}

Json::Value JsonParameters::exportParameters()
{
    Json::Value json(Json::objectValue);
    map<string, JsonParameter*>::iterator it;

    for (it=parameters.begin(); it!=parameters.end(); it++) {
        json[it->first] = it->second->serialize();
    }

    return json;
}

Json::Value JsonParameters::exportOutputs()
{
    Json::Value json(Json::objectValue);
    vector<JsonParameter*>::iterator it;

    for (it=outputs.begin(); it!=outputs.end(); it++) {
        JsonParameter *parameter = *it;
        json[parameter->getName()] = parameter->serialize();
    }

    return json;
}
        
Json::Value JsonParameters::exportAll()
{
    Json::Value json(Json::objectValue);

    json["outputs"] = exportOutputs();
    json["parameters"] = exportParameters();

    return json;
}
