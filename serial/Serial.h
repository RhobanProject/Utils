#ifndef UTILS_SERIAL_H
#define UTILS_SERIAL_H

#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

/**
 * Handles a serial port
 */
class Serial
{
    public:
        Serial(string deviceName, int deviceBaudrate);

        /**
         * Connects the serial device
         */
        int connect();

        /**
         * Closes the device
         */
        void disconnect();

        /**
         * Set the baudrate
         */
        void setSpeed(int baudrate);

        /**
         * Flushes the internal buffer
         */
        void flush();

        /**
         * Read some data
         */
        size_t receive(char *destination, size_t size);

        /**
         * Sends some data
         */
        size_t send(char *data, size_t size);

    private:
        /**
         * Device name
         */
        string deviceName;
        
        /**
         * Device baudrate
         */
        int deviceBaudrate;

        /**
         * Sets the RTS value
         */
        void setRts(int value);

        /**
         * Try to close the FD
         */
        void fdClose();

#ifdef WIN32
        HANDLE handle;
#else
        int fd;
#endif
};

#endif // UTILS_SERIAL_H
