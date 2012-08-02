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

#include <pthread.h>

#include <sockets/common.h>
#include <sockets/TCPClientBase.h>

namespace Rhoban 
{
  class TCPServerClient : public TCPClientBase
  {
  public:
    TCPServerClient(int socket);
    ~TCPServerClient();

    /**
     * Starts the client
     */
    virtual void loop()=0;

    /**
     * Runs the client (starts the thread)
     */
    virtual void run();

    /**
     * Stops the client
     */
    virtual void stop();

    /**
     * Is this client dead ?
     */
    virtual bool isDead();

    /**
     * Entry point to run a thread
     */
    static void *clientThread(void *client);

  protected:

    /**
     * Bool for isDead
     */
    bool dead;

    /**
     * Internal thread
     */
    pthread_t thread;
  };
}

#endif // _TCPSERVERCLIENT_H
