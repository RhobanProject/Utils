/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef UTILS_SERIAL_H
#define UTILS_SERIAL_H

#include <cstdlib>
#include <cstdio>
#include <string>

#ifdef WIN32
#include <windows.h>
#endif

#include <fstream>

using namespace std;

/**
 * Handles a serial port
 */
class Serial
{
    public:
        Serial(string deviceName, int deviceBaudrate);
        ~Serial();

        /**
         * Connects the serial device
         */
        int connect(bool blocking = false);

        /**
         * Closes the device
         */
        void disconnect();

        /**
         * Set the baudrate
         */
        void setSpeed(int baudrate);

        /*
         * Sets the device name
         */
        void setDevice(string name);

        /*
         * Sets the file to read characters from
         */
         void setFileDevice(string filename);

        /**
         * Flushes the internal buffer
         */
        void flush();

        /**
         * Read some data
         */
        size_t doRead(char *destination, size_t size);
        size_t receive(char *destination, size_t size, bool blocking = false);
        string receive(size_t size, bool blocking = false);
        char receiveChar();
    	unsigned short receiveShort();
    	int receiveInt();


        /**
         * Sends some data
         */
        size_t send(const char *data, size_t size);
        size_t send(string);

    	/*!
    	 * read characters until the pattern is found
    	 */
    	void seekPattern(string pattern, int max_chars_wait = 8192);

    	/*!
    	 * record all traffic to a file buffer
    	 */
    	void record(string filename);

        /**
         * Device name
         */
        string deviceName;
        bool device_is_file;

    private:

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

        /*
         * Logging
         */
       	ofstream record_stream;
        bool recording;

};

#endif // UTILS_SERIAL_H
