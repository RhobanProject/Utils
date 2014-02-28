#ifndef _JSON_SERVER_H
#define _JSON_SERVER_H

#include <json/json.h>
#include <map>
#include <string>

class JsonServer : public std::map<std::string, JsonServer*>
{
    public:
        JsonServer();

        virtual std::string process(const char *str);
        virtual std::string process(const std::string &str);
        virtual Json::Value process(const Json::Value &request);
        virtual Json::Value processSub(const std::string &sub, const Json::Value &request);

        virtual Json::Value handle(const std::string &command, const Json::Value &parameters)=0;

        bool isRunning();
        void stop();

    protected:
        bool running;
};

#endif
