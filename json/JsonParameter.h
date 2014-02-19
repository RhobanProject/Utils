#ifndef _JSON_PARAMETER_H
#define _JSON_PARAMETER_H

#include <string>
#include <json/json.h>

class JsonParameter
{
    public:
        JsonParameter(std::string name_);
        virtual std::string getName();

        // Serialization
        virtual bool canDeserialize(const Json::Value &json);
        virtual void deserialize(const Json::Value &json)=0;
        virtual Json::Value serialize()=0;

        // Accessing attributes
        JsonParameter *setAttribute(std::string name, std::string value);
        Json::Value getAttributes();
    
    protected:
        std::string name;
        Json::Value attributes;
};

template<typename T>
class JsonParameterReference : public JsonParameter
{
    public:
        JsonParameterReference(T &reference_, std::string name_)
            : JsonParameter(name_), reference(reference_) {};

        virtual Json::Value serialize() {
            return Json::Value(reference);
        }

    protected:
        T &reference;
};

template<typename T>
class JsonParameterType : public JsonParameterReference<T>
{
    public:
        JsonParameterType(T &reference_, std::string name_)
            : JsonParameterReference<T>(reference_, name_) {};
};

template<>
class JsonParameterType<double> : public JsonParameterReference<double>
{
    public:
        JsonParameterType(double &reference_, std::string name_)
            : JsonParameterReference<double>(reference_, name_) {
            setAttribute("type", "double");
        };

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isNumeric();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asDouble();
        }
};

template<>
class JsonParameterType<int> : public JsonParameterReference<int>
{
    public:
        JsonParameterType(int &reference_, std::string name_)
            : JsonParameterReference(reference_, name_) {
            setAttribute("type", "int");
        };

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isInt();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asInt();
        }
};

template<>
class JsonParameterType<float> : public JsonParameterReference<float>
{
    public:
        JsonParameterType(float &reference_, std::string name_)
            : JsonParameterReference<float>(reference_, name_) {
            setAttribute("type", "float");
        };

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isNumeric();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asFloat();
        }
};

template<>
class JsonParameterType<std::string> : public JsonParameterReference<std::string>
{
    public:
        JsonParameterType(std::string &reference_, std::string name_)
            : JsonParameterReference<std::string>(reference_, name_) {
            setAttribute("type", "string");
        };

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isString();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asString();
        }
};

template<>
class JsonParameterType<bool> : public JsonParameterReference<bool>
{
    public:
        JsonParameterType(bool &reference_, std::string name_)
            : JsonParameterReference<bool>(reference_, name_) {
            setAttribute("type", "bool");
        };

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isBool();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asBool();
        }
};

#endif
