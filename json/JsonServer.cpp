#include "JsonServer.h"
        
string JsonServer::process(const char *str)
{
    return process(string(str));
}

string JsonServer::process(const string &str)
{
    Json::Reader reader;
    Json::Value request;

    if (reader.parse(str, request)) {
        Json::Value response = process(request);
        Json::FastWriter writer;

        return writer.write(response);
    }

    return "[0,\"Unable to parse the request\"]";
}

Json::Value JsonServer::process(const Json::Value &request)
{
    Json::Value response;

    response[0] = 0;
    if (request.isArray() && request.size() >= 1 && request[0].isString()) {
        string command = request[0].asString();
        Json::Value parameters;

        if (request.size() >= 2) {
            parameters = request[1];
        }

        try {
            response[1] = handle(command, parameters);
            response[0] = 1;
        } catch (string error) {
            response[1] = error;
        } catch (...) {
            response[1] = "Error while processing command";
        }
    } else {
        response[1] = "Bad request";
    }

    return response;
}
