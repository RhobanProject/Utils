#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "Serial.h"

using namespace std;

int main()
{
    char data[] = {0xff, 0xff, 0x01, 0x04, 0x04, 0x19, 0x00, 0xde};
    char buffer[128];
    size_t size;
    Serial port("/dev/ttyUSB0", 1000000);
    
    cout << "* Connecting..." << endl;
    if (port.connect() == 0) {
        cout << "* Connected" << endl;

        cout << "* Pinging servo 1" << endl;
        size = port.send(data, 8);
        cout << "* Wrote " << size << " bytes" << endl;

        sleep(1);

        cout << "* Receiving data" << endl;
        size = port.receive(buffer, 128);
        cout << "* Got " << size << " bytes" << endl;

    } else {
        cout << "* Unable to connect on serial port" << endl;
    }
}
