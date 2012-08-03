/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*
 * test_timed_thread.cpp
 *
 *  Created on: 29 nov. 2011
 *      Author: Hugo
 */




#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "util.h"
#include "ticks.h"

#ifdef WIN32
#include <windows.h>
#endif

#include "TimedThread.h"

using namespace std;

int freq = 50;

class TestTimedThread : public TimedThread
{
    public:
        int count;
        TestTimedThread():count(0){}


    protected:
        void step()
        {
            cout << "TimedThread " << (long) this;

            if(count <freq)
                cout << " step " << count ++ << " at "<< real_time << endl;
            else
            {
                cout << " killing myself... ";
                kill_and_delete_me();
                cout << "... my last blow." << endl;
            }

        }
};

int main(int argc, char **argv)
{

    cout << "Creating thread" << endl;
    TestTimedThread * thread = new TestTimedThread();
    cout << "Initializing thread" << endl;
    thread->init(freq,false);
    //thread2->init(20,true);
    cout << "Waiting..." << endl;
    syst_wait_ms(1500);


    cout << "Creating thread2" << endl;
    TestTimedThread * thread2 = new TestTimedThread();
    cout << "Initializing thread2" << endl;
    thread2->init(freq,true);

    cout << "Creating thread3" << endl;
    TestTimedThread * thread3 = new TestTimedThread();
    cout << "Initializing thread3" << endl;
    thread3->init_suspended(freq,false);
    cout << "Waiting 300 ms before starting thread 3..." << endl;
    syst_wait_ms(300);
    cout << "Resuming thread 3" << endl;
    thread3->resume();


    syst_wait_ms(1500);
    cout << "... bye!" << endl;
    return 0;

}
