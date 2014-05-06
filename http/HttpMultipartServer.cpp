#include "HttpMultipartServer.h"

namespace Rhoban
{
    HttpMultipartServer::HttpMultipartServer(int port_)
    {
        port = port_;
    }
               
    void HttpMultipartServer::execute()
    {
        TCPServer<HttpMultipartClient>::run(port);
    }
               
    void HttpMultipartServer::pushFrame(string url, string type, string frame_)
    {
        if (currentFrame.find(url) == currentFrame.end()) {
            currentFrame[url] = 0;
        } else {
            currentFrame[url] = (currentFrame[url])%2;
        }

        int c = currentFrame[url];
        vector<string> &framesForUrl = frames[url];
        framesForUrl.resize(2);
        framesForUrl[c] = frame_;

        TCPServer<HttpMultipartClient>::lock();
        vector<HttpMultipartClient *>::iterator it;
        for (it=clients.begin(); it!=clients.end(); it++) {
            if (url == (*it)->url) {
                (*it)->setType(type);
                (*it)->pushFrame(&frames[url][c]);
            }
        }
        TCPServer<HttpMultipartClient>::unlock();
    }
}
