#include <iostream>

#define LINUX 1
#include <serial/Serial.cpp>

int main()
{
    Serial port("/dev/ttyACM0", 1000000);
    port.connect();
    port.send("\xaa", 1);
    port.disconnect();
}
