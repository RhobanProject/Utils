#ifndef _HTTP_CLIENT_H
#define _HTTP_CLIENT_H

#include <vector>
#include <string>
#include <sockets/TCPServerClient.h>

namespace Rhoban
{
    class HttpClient : public TCPServerClient
    {
        public:
            void loop();

            virtual void response()=0;

            // Receive HTTP headers
            bool readHeader();

            // Parses the HTTP headers
            bool parseHeader(const std::vector<std::string> &lines);
            string getUrl(const std::string &request);

            // Requested URL
            std::string url;
    };
}

#endif
