#include <iostream>
#include "HttpClient.h"
#include <util.h>

using namespace std;

namespace Rhoban
{
    void HttpClient::loop()
    {
        if (readHeader()) {
            response();
        }
    }
    
    bool HttpClient::readHeader()
    {
        vector<string> lines;
        string line = "";

        while (waitReady(5000)) {
            char c;
            receive(&c, 1);

            if (c != '\r') {
                if (c == '\n') {
                    if (line == "") {
                        break;
                    } else {
                        lines.push_back(line);
                    }
                    line = "";
                } else {
                    line += c;
                }
            }
        }

        return parseHeader(lines);
    }

    string HttpClient::getUrl(const string &request)
    {
        vector<string> parts;
        split(request, ' ', parts);

        if (parts.size() != 0) {
            return parts[1];
        } else {
            return "";
        }
    }

    bool HttpClient::parseHeader(const vector<string> &lines)
    {
        if (lines.size()) {
            url = getUrl(lines[0]);
            int pos = url.find("?", 0);
            if (pos >= 0) {
                url = url.substr(0, pos);
            }

            return true;
        } else {
            return false;
        }
    }
}
