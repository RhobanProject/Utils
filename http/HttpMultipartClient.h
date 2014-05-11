#ifndef _HTTP_MULTIPART_CLIENT_H
#define _HTTP_MULTIPART_CLIENT_H

#include <string>
#include "HttpClient.h"
#include <threading/Condition.h>

namespace Rhoban
{
    class HttpMultipartClient
        : public HttpClient
    {
        public:
            HttpMultipartClient();
            HttpMultipartClient(string type);
            void setType(string type_);

            void pushFrame(string *frame);
            void response();

        protected:
            Condition condition;
            string type;
            string *frame;
            bool responding;
    };
}

#endif
