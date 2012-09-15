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

    return 0;

}
