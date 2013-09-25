/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _TCPSERVERCLIENT_H
#define _TCPSERVERCLIENT_H

#include <threading/Thread.h>

#include "common.h"
#include "TCPClientBase.h"

namespace Rhoban 
{
    class TCPServerClient : public virtual TCPClientBase, public virtual Thread
    {
        public:
            TCPServerClient();
			TCPServerClient(SOCKET socket){ setSocket(socket); };
            ~TCPServerClient();

            /**
             * Starts the client
             */
            virtual void loop()=0;

            /**
             * Runs the client (starts the thread)
             */
            virtual void execute();

            /**
             * Stops the client
             */
            virtual void stop();

            /**
             * Is this client dead ?
             */
            virtual bool isDead();

            /**
             * Closes the client socket
             */
            void closeSocket();

            /**
             * Sets the socket
             */
            void setSocket(SOCKET socket);

            /**
             * Entry point to run a thread
             */
            static void *clientThread(void *client);

        protected:

            /**
             * Bool for isDead
             */
            bool dead;
    };
}

#endif // _TCPSERVERCLIENT_H
