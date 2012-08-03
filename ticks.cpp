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
 * ticks.c
 *
 *  Created on: 23 f�vr. 2010
 *      Author: hugo
 */

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#ifdef _WIN32
#include <windows.h>
#endif

#include "ticks.h"
#include "util.h"

ui32 tick_machine_is_launched = 0;
ui32 ticks_frequency = 0;
ui32 ticks =0;

void catcher( int sig ) {ticks++;}

int launch_tick_machine(ui32 frequency);

int init_tick_machine()
{
	return init_tick_machine(DEFAULT_TICKS_FREQUENCY);
}

int init_tick_machine(ui32 frequency){
  if (tick_machine_is_launched != 0 && ticks_frequency == frequency) { return 1; };

  if(frequency <= 0)
	  launch_tick_machine(DEFAULT_TICKS_FREQUENCY);
  else
	  launch_tick_machine(frequency);

  return 1;
}

ui32 get_ticks_frequency(){
	return ticks_frequency;
}


int launch_tick_machine(ui32 frequency){

	if ((frequency > MAX_TICKS_FREQUENCY)||(frequency< 0)){
		fprintf(stderr,
				"ticks.c: launche_tick_machine: tried to launch tick machine with frequency % d while max frequency is %d\n",
					frequency, MAX_TICKS_FREQUENCY);
		frequency = MAX_TICKS_FREQUENCY;
	}

#ifdef _WIN32
#else

	struct sigaction sact;
	sigemptyset( &sact.sa_mask );
	sact.sa_flags = 0;
	sact.sa_handler = catcher;
	sigaction( SIGALRM, &sact, NULL );

	/*
 	 * Set the real time interval timer
	 */
    struct itimerval value, ovalue;

    /* only usec are to be used, except for the special case frequency 1 ...*/
    if (frequency==1){
    	value.it_interval.tv_sec = 1;
    	value.it_interval.tv_usec = 0;
	    value.it_value.tv_sec = 1;
	    value.it_value.tv_usec = 0;
    }else {
    	value.it_interval.tv_sec = 0;
       	value.it_interval.tv_usec = 1000000 / frequency;
        value.it_value.tv_sec = 0;
        value.it_value.tv_usec = 1000000 / frequency;
    }

    setitimer( ITIMER_REAL, &value, &ovalue );
#endif
    tick_machine_is_launched=1;
    ticks_frequency = frequency;
    ticks=0;
    return 0;
}
void wait_next_tick(void){
	wait_n_ticks(1);
}

void wait_n_ticks(ui32 tick_nb){
	if(!tick_machine_is_launched){
		fprintf(stderr,"ticks: wait_n_ticks: launching tick machine with default tick frequency %d.\n",
				DEFAULT_TICKS_FREQUENCY);
		init_tick_machine(DEFAULT_TICKS_FREQUENCY);
	}

#ifdef _WIN32
	int tick_duration = 1000000/ticks_frequency;
   	for (;tick_nb>0; tick_nb--) usleep(tick_duration);
#else
	sigset_t block_set;
    sigfillset( &block_set );
    sigdelset( &block_set, SIGALRM);

    while(tick_nb>0){
    	sigsuspend( &block_set );
    	tick_nb--;
    }
#endif
}

void sleep_ticks(struct timeval duration)
{
	sleep_ms_ticks(duration.tv_sec*1000 + duration.tv_usec/1000);
}

void sleep_ms_ticks(ui32 ms) {
#ifdef _WIN32
	Sleep(ms);
	//usleep(ms%1000);
	//for (int i=0; i<ms; i++) usleep(1000);
#else
	if (ms<=0) {
		fprintf(stderr,"ticks.c: wait_n_ticks: asked for waiting %d ms, waiting for next tick instead\n",ms);
		wait_next_tick();
	}

	ui32 ticks_to_wait = (ms * ticks_frequency) / 1000;
	if(ticks_to_wait==0){
		wait_n_ticks(1);
	}else{
		wait_n_ticks(ticks_to_wait);
	}
#endif
}


/*!
 * returns the number of musec since init of the time machine
 * @return
 */
ui32 get_msec()
{
#ifdef _WIN32
	return 0;
#else
	return (1000*ticks)/ticks_frequency;
#endif
}

void get_tick_machine_time(struct timeval * clock)
{
#ifdef _WIN32
#else
	struct itimerval pvalue;
	getitimer( ITIMER_REAL, &pvalue );
	clock->tv_sec = pvalue.it_value.tv_sec;
	clock->tv_usec = pvalue.it_value.tv_usec;
#endif
}

void sleep_ms(int ms)
{
  sleep_ms_ticks(ms);
}

void wait_ms(int ms)
{
  sleep_ms_ticks(ms);
}

void sleep_ms(struct timeval duration)
{
  sleep_ticks(duration);
}

void decrease(struct timeval & chrono, struct timeval & duration)
{
  chrono.tv_sec -= duration.tv_sec;
  chrono.tv_usec -= duration.tv_usec;
}

void increase(struct timeval & chrono, struct timeval & duration)
{
  chrono.tv_usec += duration.tv_usec;
  chrono.tv_sec += duration.tv_sec + chrono.tv_usec/1000000;
  chrono.tv_usec %= 1000000;
}

bool is_after(struct timeval & time_to_check, struct timeval & reference)
{
  long diff =       ((time_to_check.tv_sec - reference.tv_sec)*1000000 + (time_to_check.tv_usec - reference.tv_usec));
  return (diff>=0);
}

double to_secs(struct timeval & duration)
{
  return duration.tv_usec/1000000.0 +duration.tv_sec;
}

string timevalToString(const struct timeval & time)
{
  return std::string(my_itoa(time.tv_sec)+" secs "+my_itoa(time.tv_usec)+ " musecs");
}


