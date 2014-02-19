#ifndef _JSON_PARAMETERS_H
#define _JSON_PARAMETERS_H

#include <string>
#include <map>
#include <vector>
#include "JsonParameter.h"

class JsonParameters
{
    public:
        virtual ~JsonParameters();

        // Getting outputs and parameters
        std::vector<JsonParameter*> getOutputs();
        std::vector<JsonParameter*> getParameters();
        JsonParameter *getParameter(std::string name);

        // Importing parameters
        void importParameters(Json::Value parameters);
        Json::Value exportParameters();
        Json::Value exportOutputs();
        Json::Value exportAll();

        // Checking if a parameter is present
        bool hasParameter(std::string name);

        // Registering a new parameter
        template<typename T>
        JsonParameterType<T> *addParameter(T &reference, std::string name) {
            JsonParameterType<T> *parameter = new JsonParameterType<T>(reference, name);
            parameters[name] = parameter;

            return parameter;
        }

        // Registering a new output
        template<typename T>
        JsonParameterType<T> *addOutput(T &reference, std::string name) {
            JsonParameterType<T> *output = new JsonParameterType<T>(reference, name);
            outputs.push_back(output);

            return output;
        }

    protected:
        std::map<std::string, JsonParameter*> parameters;
        std::vector<JsonParameter*> outputs;
};

#endif
