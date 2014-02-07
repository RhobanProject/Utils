#ifndef _JSON_PARAMETER_H
#define _JSON_PARAMETER_H

#include <string>
#include <json/json.h>

using namespace std;

class JsonParameter
{
    public:
        JsonParameter(string name_, string description_);

        virtual void deserialize(const Json::Value &json)=0;
        virtual Json::Value serialize()=0;

        virtual string getName();
        virtual string getDescription();
        virtual bool canDeserialize(const Json::Value &json);
    
    protected:
        string name;
        string description;
};

template<typename T>
class JsonParameterReference : public JsonParameter
{
    public:
        JsonParameterReference(T &reference_, string name_, string description_)
            : JsonParameter(name_, description_), reference(reference_) {};

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
        JsonParameterType(T &reference_, string name_, string description_)
            : JsonParameterReference<T>(reference_, name_, description_) {};
};

template<>
class JsonParameterType<double> : public JsonParameterReference<double>
{
    public:
        JsonParameterType(double &reference_, string name_, string description_)
            : JsonParameterReference<double>(reference_, name_, description_) {};

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
        JsonParameterType(int &reference_, string name_, string description_)
            : JsonParameterReference(reference_, name_, description_) {};

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
        JsonParameterType(float &reference_, string name_, string description_)
            : JsonParameterReference<float>(reference_, name_, description_) {};

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isNumeric();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asFloat();
        }
};

template<>
class JsonParameterType<string> : public JsonParameterReference<string>
{
    public:
        JsonParameterType(string &reference_, string name_, string description_)
            : JsonParameterReference<string>(reference_, name_, description_) {};

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
        JsonParameterType(bool &reference_, string name_, string description_)
            : JsonParameterReference<bool>(reference_, name_, description_) {};

        virtual bool canDeserialize(const Json::Value &json) {
            return json.isBool();
        }

        void deserialize(const Json::Value &json) {
            reference = json.asBool();
        }
};

#endif
