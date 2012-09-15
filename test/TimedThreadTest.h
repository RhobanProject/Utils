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
	int count;
	MyThread2(string name):count(0){this->name = name;}


protected:
	string name;
	void step()
	{
		cout <<  name;
		if(count < FREQ)
			cout << " step " << count ++ << " at "<< real_time << " and frequency "<< frequency << endl;
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
            MyThread2 * thread = new MyThread2("Thread1");
            cout << "Initializing thread" << endl;
            thread->init(FREQ);
            //thread2->init(20,true);
            //cout << "Waiting 2 secs..." << endl;
            //syst_wait_ms(2000);

            syst_wait_ms(10000);

            cout << "Creating thread2" << endl;
            MyThread2 * thread2 = new MyThread2("Thread2");
            cout << "Initializing thread2" << endl;
            thread2->init(FREQ * 2);

            syst_wait_ms(10000);

            cout << "Creating thread3" << endl;
            MyThread2 * thread3 = new MyThread2("Thread3");
            cout << "Initializing thread3" << endl;
            thread3->init_suspended(FREQ/2);
            cout << "Waiting 300 ms before starting thread 3..." << endl;
            //syst_wait_ms(2000);
            cout << "Resuming thread 3" << endl;
            thread3->resume();


            syst_wait_ms(10000);


            cout << "... bye!" << endl;
        }

    protected:
        void _run() {
            testTimedThread();
            testTimedThread2();
        }
};
