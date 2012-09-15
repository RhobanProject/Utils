/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <ticks.h>
#include <threading/TimedThread.h>
#include <timing/TickMachine.h>

#include <tests/TestCase.h>

#define OUTPUT(msg...) printf(msg); fflush(stdout);

#define FREQ 50

int n = 0;

class MyThread : public TimedThread
{
    public:
        MyThread() : counter(0)
    {
    }

        void step() {
            counter++;
        };

        int counter ;
};

class MyThread2 : public TimedThread
{
    public:
        MyThread2() : count(0)
        {
        }
        
        int count;

    protected:
        void step()
        {
            cout << "TimedThread " << (long) this;

            if (count <FREQ)
                cout << " step " << count ++ << " at "<< real_time << endl;
            else
            {
                cout << " killing myself... ";
                kill_and_delete_me();
                cout << "... my last blow." << endl;
            }

        }
};

class TimedThreadTest : public TestCase
{
    public:
        void testTimedThread()
        {
            MyThread my_thread;
            my_thread.init(10.0);
            OUTPUT("Running a 10Hz TimedThread for 1.9s\n");
            syst_wait_ms(1900);
            my_thread.kill();
            assertEquals(my_thread.counter, 20);
        }

        /**
         * TODO: Use assertions!
         */
        void testTimedThread2()
        {
            cout << "Creating thread" << endl;
            MyThread2 * thread = new MyThread2();
            cout << "Initializing thread" << endl;
            thread->init(FREQ);
            cout << "Waiting..." << endl;
            syst_wait_ms(1500);


            cout << "Creating thread2" << endl;
            MyThread2 * thread2 = new MyThread2();
            cout << "Initializing thread2" << endl;
            thread2->init(FREQ);

            cout << "Creating thread3" << endl;
            MyThread2 * thread3 = new MyThread2();
            cout << "Initializing thread3" << endl;
            thread3->init_suspended(FREQ);
            cout << "Waiting 300 ms before starting thread 3..." << endl;
            syst_wait_ms(300);
            cout << "Resuming thread 3" << endl;
            thread3->resume();


            syst_wait_ms(1500);
            cout << "... bye!" << endl;
        }

    protected:
        void _run() {
            testTimedThread();
            testTimedThread2();
        }
};
