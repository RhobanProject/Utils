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

using namespace std;

int freq = 50;

class TestTimedThread : public TimedThread
{
public:
	int count;
	TestTimedThread(string name):count(0){this->name = name;}


protected:
	string name;
	void step()
	{
		cout <<  name;
//		if(count < 3*freq)
			cout << " step " << ++count << " at "<< real_time << " and frequency "<< frequency << endl;
//		else
//		{
//			cout << " killing myself... ";
//			kill_and_delete_me();
//			cout << "... my last blow." << endl;
//		}

	}
};

int main(int argc, char **argv)
{

	cout << "Creating thread" << endl;
	TestTimedThread * thread = new TestTimedThread("Thread1");
	cout << "Initializing thread" << endl;
	thread->init(freq*2);
	//thread2->init(20,true);
	//cout << "Waiting 2 secs..." << endl;
	syst_wait_ms(5000);


	cout << "Creating thread2" << endl;
	TestTimedThread * thread2 = new TestTimedThread("Thread2");
	cout << "Initializing thread2" << endl;
	thread2->init(freq);

	cout << "Creating thread3" << endl;
	TestTimedThread * thread3 = new TestTimedThread("Thread3");
	cout << "Initializing thread3" << endl;
	thread3->init_suspended(freq/2);
	cout << "Waiting 300 ms before starting thread 3..." << endl;
	//syst_wait_ms(2000);
	cout << "Resuming thread 3" << endl;
	thread3->resume();


	syst_wait_ms(10000);


	cout << "... bye!" << endl;
	return 0;

}

// TODO est-ce qu'un thread peut dire qu'il est mort:
// par exemple step pourrait retourner un booleen

// Est-ce que ticks.h est toujours utilis� ?

/*****************************************************************************/
