#ifndef _HTTP_MULTIPART_SERVER_H
#define _HTTP_MULTIPART_SERVER_H

#include <map>
#include <iostream>
#include <sockets/TCPServer.h>
#include <threading/Thread.h>
#include "HttpMultipartClient.h"

namespace Rhoban
{
    class HttpMultipartServer
        : public TCPServer<HttpMultipartClient>,
        public Thread
    {
        public:
               HttpMultipartServer(int port_);

               void execute();
               void pushFrame(string url, string type, const string & frame);

        protected:
               std::map<std::string, int> currentFrame;
               std::map<std::string, std::vector<std::string> > frames;
               std::string type;
               int port;
    };
}

#endif
