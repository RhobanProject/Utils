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
#include <sys/time.h>
#include <unistd.h>

#ifdef WIN32
#include <windows.h>
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



void sleep_ms_ticks(ui32 ms);
void sleep_ticks(struct timeval duration);

inline void syst_wait_ms(int ms)
{
#ifndef WIN32
	usleep(1000 * ms);
#else
	Sleep(ms);
#endif
};
void sleep_ms(ui32 ms);
void sleep_ms(int ms); // TODO pas terrible... les 2 sleep_ms...
void wait_ms(int ms);
void sleep_ms(struct timeval duration);
void decrease(struct timeval & chrono, struct timeval & duration);
void increase(struct timeval & chrono, struct timeval & duration);
bool is_after(struct timeval & time_to_check, struct timeval & reference);
double to_secs(struct timeval & duration);
string timevalToString(const struct timeval & time);

/*!
 * returns the number of millisec or musecs since init of the time machine
 * @return
 */
ui32 get_msec();
void get_tick_machine_time(struct timeval * clock);


#endif /* TICKS_H_ */
