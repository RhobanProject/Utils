#include <iostream>
#include <sstream>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

using google::protobuf::io::ArrayInputStream;
using google::protobuf::io::CodedInputStream;

// Routing system
std::string COMMAKER_CLASS ::process(const std::string &request)
{
    ArrayInputStream stream(request.c_str(), request.size());
    CodedInputStream coded(&stream);
    unsigned int command;
    if (!coded.ReadLittleEndian32(&command)) {
        throw std::string("Unable to read the command number.");
    }
    std::string requestString(request.c_str()+4, request.size()-4);

    return process(command, requestString);
}

std::string COMMAKER_CLASS ::process(unsigned int command, const std::string &request)
{
    switch (command) {
#define COMMAND(id, name, requestType, resultType) \
        case id : \
            return process_ ## name (request); \
            break;
#include COMMAKER_COMMANDS
#undef COMMAND
    } 

    std::ostringstream oss;
    oss << "Unknown command: " << command;
    throw oss.str();
}

// Trivial implementations
#define COMMAND(id, name, requestType, resultType) \
    bool COMMAKER_CLASS :: name (const requestType &request, resultType &response) { \
        return false; \
    }
#include COMMAKER_COMMANDS
#undef COMMAND

// Processing commands
#define COMMAND(id, name, requestType, resultType) \
    std::string COMMAKER_CLASS ::process_ ## name (const std::string &requestString) { \
        requestType request; \
        resultType result; \
        \
        if (!request.ParseFromString(requestString)) { \
            std::ostringstream oss; \
            oss << #name << ": can't read request"; \
            throw oss.str(); \
        } \
        \
        if (! name (request, result)) { \
            std::ostringstream oss; \
            oss << #name << ": can't process request"; \
            throw oss.str(); \
        } \
        \
        std::string responseString; \
        if (!result.SerializeToString(&responseString)) { \
            std::ostringstream oss; \
            oss << #name << ": can't serialize response"; \
            throw oss.str(); \
        } \
        \
        return responseString; \
    }
#include COMMAKER_COMMANDS
#undef COMMAND
