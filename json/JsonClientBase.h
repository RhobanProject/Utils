#ifndef _JSON_CLIENT_BASE_H
#define _JSON_CLIENT_BASE_H

#include <string>
#include <json/json.h>

using namespace std;

class JsonClientBase
{
    public:
        virtual Json::Value invoke(const Json::Value &request)=0;
        virtual Json::Value invoke(const string &command, const Json::Value &parameters = Json::Value());

    protected:
        Json::Value buildRequest(const string &command, const Json::Value &parameters = Json::Value());
};

#endif
