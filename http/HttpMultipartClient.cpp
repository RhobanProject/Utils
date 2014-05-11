#include <iostream>
#include <sstream>
#include <timing/sleep.h>
#include "HttpMultipartClient.h"

using namespace std;

namespace Rhoban
{
    HttpMultipartClient::HttpMultipartClient()
    {
        type = "text/plain";
        responding = false;
    }

    HttpMultipartClient::HttpMultipartClient(string type_)
        : HttpClient()
    {
        type = type_;
    }
            
    void HttpMultipartClient::setType(string type_)
    {
        type = type_;
    }

    void HttpMultipartClient::pushFrame(string *frame_)
    {
        if (responding) {
            frame = frame_;
            condition.broadcast();
        }
    }

    void HttpMultipartClient::response()
    {
        condition.lock();
        responding = true;
        string boundary = "--RhobanMultipartBoundary\r\n";
        ostringstream oss;
        oss << "HTTP/1.0 200 OK\r\n";
        oss << "Content-type: multipart/x-mixed-replace; boundary=" << boundary;
        oss << "\r\n";
        transmitString(oss.str());

        char dummy;
        setBlocking(false);
        while (!isDead()) {
            receive(&dummy, 1);

            condition.wait();
            oss.str("");
            oss << boundary;
            oss << "Content-type: " << type << "\r\n";
            oss << "Content-length: " << frame->length() << "\r\n";
            oss << "\r\n" << *frame;
            transmitString(oss.str());
        }
        condition.unlock();
    }
}
