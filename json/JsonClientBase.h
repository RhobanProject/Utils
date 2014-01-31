#ifndef _JSON_CLIENT_BASE_H
#define _JSON_CLIENT_BASE_H

#include <map>
#include <string>
#include <json/json.h>

using namespace std;

class JsonClientBase
{
    public:
        JsonClientBase();
        JsonClientBase(JsonClientBase *parent, string target);
        void set(JsonClientBase *parent, string target);

        virtual Json::Value doInvoke(const Json::Value &request);
        virtual Json::Value invoke(const string &command, const Json::Value &parameters = Json::Value());
        
        JsonClientBase &operator[](const string &target);
        JsonClientBase &to(const string &target);

    protected:
        Json::Value buildRequest(const string &command, const Json::Value &parameters = Json::Value());
        map<string, JsonClientBase> targets;
        JsonClientBase *parent;
        string target;
};

#endif
