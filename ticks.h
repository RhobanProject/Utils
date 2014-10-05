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

/*! \brief sleeps until next_tick */
void wait_next_tick(void);

void wait_n_ticks(ui32 tick_nb);

/* compute a string containing hour and date and which can be used in a filename */
string date_to_filename();

void sleep_ms_ticks(ui32 ms);
void sleep_ticks(Rhoban::chrono duration);

inline void syst_wait_ms(int ms)
{
#ifndef WIN32
	usleep(1000 * ms);
#else
	Sleep(ms);
#endif
}
inline void syst_wait_us(int us)
{
#ifndef WIN32
	usleep(us);
#else
	Sleep(us / 1000);
#endif
}

void sleep_ms(ui32 ms);
void sleep_ms(int ms); // TODO pas terrible... les 2 sleep_ms...
void wait_ms(int ms);
void sleep_ms(Rhoban::chrono duration);
void decrease(Rhoban::chrono & chronoo, Rhoban::chrono & duration);
void increase(Rhoban::chrono & chronoo, Rhoban::chrono & duration);
bool is_after(Rhoban::chrono & time_to_check, Rhoban::chrono & reference);
double to_secs(Rhoban::chrono & duration);
string chronoToString(const Rhoban::chrono & time);

/*!
 * returns the number of millisec or musecs since init of the time machine
 * @return
 */
ui32 get_msec();
void get_tick_machine_time(Rhoban::chrono * clock);


#endif /* TICKS_H_ */
