#include <iostream>
#include <string>
#ifdef HAVE_ZMQ
#include <zmq.h>
#include <zhelpers.h>
#include "ZMQGraph.h"
#endif
#include "Curve.h"

using namespace std;

ZMQGraph::ZMQGraph(string address)
{
#ifdef HAVE_ZMQ
    void *context = zmq_ctx_new();
    socket = zmq_socket(context, ZMQ_REP);
    zmq_bind(socket, address.c_str());
    start(NULL);
#endif
}

void ZMQGraph::execute()
{
#ifdef HAVE_ZMQ
    char *message;
    double time;
    ostringstream stream;

    while (1) {
        message = s_recv(socket);
        
        if (message == NULL) {
            perror("zmq");
            continue;
        }

        time = atof(message);

        for (vector<Curve*>::iterator it=curves.begin(); it!=curves.end(); it++) {
            Curve *curve = (*it);
            stream.str("");
            vector<pair<double, double> > vals = curve->getValues(time);
            stream << curve->name << endl;

            for (vector<pair<double, double> >::iterator k = vals.begin(); k != vals.end(); k++) {
                pair<double, double> p = (*k);
                stream << p.first << ", " << p.second << endl;
            }

            if ((it+1)!=curves.end()) {
                s_sendmore(socket, (char*)stream.str().c_str());
            } else {
                s_send(socket, (char *)stream.str().c_str());
            }
        }
        free(message);
    }
#endif
}

