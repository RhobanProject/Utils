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
 * ticks.h
 *
 * Tick machine
 *  Created on: 23 f�vr. 2010
 *      Author: hugo
 */

#ifndef TICKS_H_
#define TICKS_H_

#include "util.h"
#include <timing/chrono.h>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/*! \brief ticks frequency */
#define DEFAULT_TICKS_FREQUENCY 50
#define MAX_TICKS_FREQUENCY 100


/*! \brief Initializes the tick machine
 *  if frequency is negative or 0, default frequency is used
 *  also used to change the frequency */
int init_tick_machine();
int init_tick_machine(ui32 frequency);

/*! \return The current tick frequency */
unsigned int get_ticks_frequency();

/*! \brief sys_wait_mss until next_tick */
void wait_next_tick(void);

void wait_n_ticks(ui32 tick_nb);



void sys_wait_ms_ms_ticks(ui32 ms);
void sys_wait_ms_ticks(chrono duration);

inline void syst_wait_ms(int ms)
{
#ifndef WIN32
	usys_wait_ms(1000 * ms);
#else
	sys_wait_ms(ms);
#endif
}
void sys_wait_ms_ms(ui32 ms);
void sys_wait_ms_ms(int ms); // TODO pas terrible... les 2 sys_wait_ms_ms...
void wait_ms(int ms);
void sys_wait_ms_ms(chrono duration);
void decrease(chrono & chronoo, chrono & duration);
void increase(chrono & chronoo, chrono & duration);
bool is_after(chrono & time_to_check, chrono & reference);
double to_secs(chrono & duration);
string chronoToString(const chrono & time);

/*!
 * returns the number of millisec or musecs since init of the time machine
 * @return
 */
ui32 get_msec();
void get_tick_machine_time(chrono * clock);


#endif /* TICKS_H_ */
