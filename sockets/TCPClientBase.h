/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _TCPCLIENTBASE_H
#define _TCPCLIENTBASE_H

#include <string>

#include <sockets/common.h>

using namespace std;

namespace Rhoban
{
    class TCPClientBase
    {
        public:
            /**
             * Sends a buffer
             */
            int transmit(const char *buffer, int size);

            /**
             * Sends a buffer until everything was sent
             */
            void transmitAll(const char *buffer, int size);

            /**
             * Sends a string
             */
            void transmitString(string str, bool lineTerminates = false);

            /**
             * Transmits a formatted string
             */
            void transmitFormat(const char *format, ...);

            /**
             * Receive data (returns the size actually received)
             */
            int receive(char *buffer, int size);

            /**
             * Receive all the data
             */
            void receiveAll(char *buffer, int size);

            /**
             * Receives a string
             */
            string receiveString(bool lineTerminates = false);
            string receiveStringSize(int size);
            string receiveStringMaxSize(int size);

            /**
             * Receives a formatted string
             */
            void receiveFormat(const char *format, ...);

            /**
             * Change to block mode / non block mode
             */
            void setBlocking(int blocking);

            /**
             * Waits the internal socket to be ready for reading
             */
            bool waitReady(int timeout);

            /**
             * Closes the connection
             */
            void stop();

            /**
             * Is the connection established ?
             */
            virtual bool isConnected();

        protected:
            /**
             * Internal socket
             */
            volatile SOCKET clientSocket;
            
            /**
             * State
             */
            bool connected;
    };
}

#endif // _TCPCLIENTBASE_H
