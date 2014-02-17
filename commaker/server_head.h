class COMMAKER_CLASS
{
public:
std::string process(const std::string &request);
std::string process(unsigned int command, const std::string &request);

#define COMMAND(id, name, requestType, responseType) \
    std::string process_ ## name (const std::string &request); \
    virtual bool name (const requestType &request, responseType &response);

#include COMMAKER_COMMANDS
#undef COMMAND
};
