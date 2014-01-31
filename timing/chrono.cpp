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
/*! \file    chrono.c
 *  \author  Olivier Ly
 *  \date    2009-10
 *
 *  \brief   Basic tools for time measure.
 *****************************************************************************/

#include <stdlib.h>
#include "chrono.h"

/*!\brief compute tv0-tv1 and put it into dtv */
void compute_tv_diff(chrono *tv0,
		     chrono *tv1,
		     chrono *dtv) {
  if (tv0->tv_sec == tv1->tv_sec) {
    dtv->tv_sec = 0;
    dtv->tv_usec = tv0->tv_usec - tv1->tv_usec;
  }
  else {
    long int usec_diff;    
    dtv->tv_sec = tv0->tv_sec - tv1->tv_sec - 1;
    usec_diff = tv0->tv_usec + (1000000 - tv1->tv_usec);
    if (usec_diff > 1000000) {
      dtv->tv_sec = dtv->tv_sec + 1;
      dtv->tv_usec = usec_diff - 1000000;      
    }
    else
      dtv->tv_usec = usec_diff;      
  }
}

#ifdef MSVC
			 int gettimeofday (chrono *tp, void *tz)
{
struct _timeb timebuffer;
	_ftime (&timebuffer);
	tp->tv_sec = timebuffer.time;
	tp->tv_usec = timebuffer.millitm * 1000;
return 0;
}

#endif

			 chrono * chrono_create() {
  chrono * chr = (chrono*) malloc(sizeof(chrono));
  chrono_reset(chr);
  return chr;
}

void chrono_reset(chrono * chr) {
  gettimeofday(chr,NULL);
}

void delete_chrono(chrono * chr) {
  free(chr);
}

long int chrono_sec(chrono * chr) {
  chrono tv, tv_diff;
  gettimeofday(&tv,NULL);
  compute_tv_diff(&tv, chr, &tv_diff);
  return tv_diff.tv_sec;
}

long int chrono_msec(chrono * chr) {
  chrono tv, tv_diff;
  gettimeofday(&tv,NULL);
  compute_tv_diff(&tv, chr, &tv_diff);
  return tv_diff.tv_sec * 1000 + tv_diff.tv_usec / 1000;
}

long int chrono_usec(chrono * chr) {
  chrono tv, tv_diff;
  gettimeofday(&tv,NULL);
  compute_tv_diff(&tv, chr, &tv_diff);
  return tv_diff.tv_sec * 1000000 + tv_diff.tv_usec;
}

/*****************************************************************************/
/*****************************************************************************/

Chrono::Chrono()
{
    reset();
}
        
double Chrono::getTime()
{
    return chrono_usec(&chr)*0.000001;
}

void Chrono::reset()
{
    chrono_reset(&chr);
}
