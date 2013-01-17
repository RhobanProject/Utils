/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H

#include "common.h"
#include "TCPClientBase.h"

namespace Rhoban
{
    class TCPClient : virtual public TCPClientBase
    {
        public:
            TCPClient();
            ~TCPClient();

            /**
             * Try to connect to address:port
             */
            virtual void connectTo(const char *address, int port);

            /**
             * Is the connection established ?
             */
            virtual bool isConnected();

        protected:
            /**
             * State
             */
            bool connected;
    };
}

#endif //  _TCPCLIENT_H
