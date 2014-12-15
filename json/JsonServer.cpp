#include <sstream>
#include "JsonServer.h"

using std::string;
using std::ostringstream;
        
JsonServer::JsonServer()
    : running(true)
{
}
        
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

Json::Value JsonServer::processSub(const string &sub, const Json::Value &request)
{
    iterator it = find(sub);

    if (it != end()) {
        return it->second->process(request);
    } else {
        ostringstream oss;
        oss << "Unknown sub: " << sub;

        throw oss.str();
    }
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
            if (command == "sub") {
                if (parameters.isArray() && parameters.size() == 2) {
                    return processSub(parameters[0].asString(), parameters[1]);
                } else {
                    throw string("Malformed sub request");
                }
            } else if (command == "ping") {
                response[0] = 1;
                response[1] = "pong";
            } else {
                response[1] = handle(command, parameters);
                response[0] = 1;
            }
        } catch (string error) {
            response[1] = error;
        } catch (std::runtime_error e) {
            response[1] = e.what();
        } catch (...) {
            response[1] = "Error while processing command";
        }
    } else {
        response[1] = "Bad request";
    }

    return response;
}
        
bool JsonServer::isRunning()
{
    return running;
}

void JsonServer::stop()
{
    running = false;
}
