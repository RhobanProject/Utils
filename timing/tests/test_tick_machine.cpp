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
 * test_tick_machine.cpp
 *
 *  Created on: 20 juil. 2011
 *      Author: hugo
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

#include "TickMachine.h"

using namespace std;

int freq1 = 50;
int freq2 = 10;

int main(int argc, char **argv)
{
	cout << "Creating timer 1 at " << freq1 << " Hz " << endl;
	TickTimer timer1(freq1);
	cout << "Creating timer 2 at " << freq2 << " Hz " << endl;
	TickTimer timer2(freq2);
	

	cout << "Testing timer 1" << endl;
	for(int i= 0 ; i<= freq1; i++)
	{
		timer1.wait_next_tick();
		cout << "Tick " << i << " of timer 1 at " << freq1 << "Hz :" << timer1.real_time << endl; 
	}

	cout << "Testing timer 2" << endl;
	for(int i= 0 ; i<= freq2; i++)
	{
		timer2.wait_next_tick();
		cout << "Tick " << i << " of timer 2 at " << freq2 << "Hz :" << timer2.real_time << endl; 
	}
	
	cout << "Changing timer 1 frequency" << endl;
	timer1.set_frequency(freq2);
	for(int i= 0 ; i<= freq2; i++)
	{
		timer1.wait_next_tick();
		cout << "Tick " << i << " of timer 1 at " << freq2 << "Hz :" << timer1.real_time << endl; 
	}
	
}
