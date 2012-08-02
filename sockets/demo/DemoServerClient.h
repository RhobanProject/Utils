/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef _DEMOSERVERCLIENT_H
#define _DEMOSERVERCLIENT_H

#include <sockets/TCPServerClient.h>

namespace Rhoban
{
    class DemoServerClient : public TCPServerClient
    {
        public:
            DemoServerClient(int socket);

            void loop();
    };
}

#endif //  _DEMOSERVERCLIENT_H
