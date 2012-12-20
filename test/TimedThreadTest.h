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
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "util.h"
#include "ticks.h"

#ifdef WIN32
#include <windows.h>
#endif

#include <ticks.h>
#include <threading/TimedThread.h>
#include <timing/TickMachine.h>
#include <tests/TestCase.h>

using namespace std;

int freq = 50;
double accuracy = 0.01;


class TimedThreadTest : public TestCase
{
	class MyTimedThread : 	public TimedThread
	{
	public:
		int count;
		MyTimedThread(string name):count(0){this->name = name;}

		bool accurate()
		{
			return real_time - count*1.0/frequency <= accuracy;
		}

	protected:
		string name;
		void step()
		{
			//		if(count < 3*freq)
			if(count++ % 10 == 0)
			{
				cout <<  name;
				cout << " step " << count << " at "<< real_time << " and frequency "<< frequency << endl;
			}

			//		else
			//		{
			//			cout << " killing myself... ";
			//			kill_and_delete_me();
			//			cout << "... my last blow." << endl;
			//		}

		}
	};


	public:

	void testAccuracy()
	{
		cout << "Creating thread" << endl;
		MyTimedThread thread1("Thread1");
		cout << "Initializing thread" << endl;
		thread1.init(freq*2);
		//thread2->init(20,true);
		//cout << "Waiting 2 secs..." << endl;
		syst_wait_ms(2000);


		cout << "Creating thread2" << endl;
		MyTimedThread thread2("Thread2");
		cout << "Initializing thread2" << endl;
		thread2.init(freq);

		cout << "Creating thread3" << endl;
		MyTimedThread thread3("Thread3");
		cout << "Initializing thread3" << endl;
		thread3.init_suspended(freq/2);
		cout << "Waiting 300 ms before starting thread 3..." << endl;
		//syst_wait_ms(2000);
		cout << "Resuming thread 3" << endl;
		thread3.resume();


		syst_wait_ms(2000);

		assertTrue(thread1.accurate());
		assertTrue(thread2.accurate());
		assertTrue(thread3.accurate());

	}

	protected:
	void _run()
	{
		testAccuracy();
	}
};

/*****************************************************************************/
