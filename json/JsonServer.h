#ifndef _JSON_SERVER_H
#define _JSON_SERVER_H

#include <json/json.h>
#include <map>
#include <string>

using namespace std;

class JsonServer : public map<string, JsonServer*>
{
    public:
        virtual string process(const char *str);
        virtual string process(const string &str);
        virtual Json::Value process(const Json::Value &request);
        virtual Json::Value processSub(const string &sub, const Json::Value &request);

        virtual Json::Value handle(const string &command, const Json::Value &parameters)=0;
};

#endif
