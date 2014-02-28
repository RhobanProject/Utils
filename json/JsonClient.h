#ifndef _JSON_CLIENT_H
#define _JSON_CLIENT_H

#include <json/json.h>
#include <string>
#include "JsonClientBase.h"

template<typename T>
class JsonClient : public JsonClientBase
{
    public:
        JsonClient(T &sender_)
            : sender(sender_)
        {
        }

        std::string process(const char *str)
        {
            return process(std::string(str));
        }

        std::string process(const std::string &str)
        {
            return sender.process(str);
        }

        using JsonClientBase::invoke;

        Json::Value doInvoke(const Json::Value &request)
        {
            Json::Value response;
            Json::FastWriter writer;
            std::string resp = process(writer.write(request));
            Json::Reader reader;

            if (!reader.parse(resp, response)) {
                throw std::string("Unable to parse server response");
            }

            if (!response.isArray() || !response[0].isInt()) {
                throw std::string("Malformed response");
            }

            if (!response[0].asInt()) {
                throw response[1].asString();
            }

            return response[1];
        }

    protected:
        T &sender;
};

#endif
