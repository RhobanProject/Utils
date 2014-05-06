#include <sstream>
#include <iostream>
#include <string>
#include <sockets/TCPServer.h>
#include <timing/sleep.h>
#include <http/HttpMultipartServer.h>
#include <util.h>
#include <file_mngt.h>

using namespace std;
using namespace Rhoban;

int main(int argc, char *argv[])
{
    HttpMultipartServer server(8080);

    cout << "Running server..." << endl;
    server.start();

    int num;
    while (true) {
        num = (num+1)%360;
        ostringstream oss;
        oss << "/tmp/test_" << num << ".jpg";
        string frame = file_get_contents(oss.str());
        server.pushFrame("/", "image/jpeg", frame);

        oss.str("");
        oss << "<html><title>" << system_time() << "</title></html>";
        server.pushFrame("/time", "text/html", oss.str());

        ms_sleep(100);
    }
}
