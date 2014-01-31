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
/*! \file    chrono.h
 *  \author  Olivier Ly
 *  \date    2009-10
 *
 *  \brief   Basic tools for time measure.
 *****************************************************************************/
#ifndef CHRONO_H
#define CHRONO_H

/*****************************************************************************/
/*!\brief A chrono is just a type value
 *****************************************************************************/

#ifdef MSVC
#include <time.h>
#include <sys/timeb.h>

struct tttt {
        long    tv_sec;        
        long    tv_usec;      
};

typedef struct tttt chrono;
int gettimeofday (chrono *tp, void *tz);
#else
#include <time.h>
#include <sys/time.h>
typedef struct timeval chrono;
#endif


/*****************************************************************************/
/*!\brief Reset the chrono
 * \param chr the chrono to be resetted.
 *****************************************************************************/
void chrono_reset(chrono * chr);

/*****************************************************************************/
/*!\brief Create a new chono.
 * \return the address of the chrono.
 *****************************************************************************/
chrono * chrono_create();

/*****************************************************************************/
/*!\brief kill a chrono and free its resources
 *****************************************************************************/
void delete_chrono(chrono * chr);

/*****************************************************************************/
/*!\brief Gives the number of second elapsed from the last timer reset. 
 *****************************************************************************/
long int chrono_sec(chrono * chr);

/*****************************************************************************/
/*!\brief Gives the number of milli second elapsed from the last timer reset. 
 *****************************************************************************/
long int chrono_msec(chrono * chr);

/*****************************************************************************/
/*!\brief Gives the number of micro second elapsed from the last timer reset. 
 *****************************************************************************/
long int chrono_usec(chrono * chr);

class Chrono
{
    public:
        Chrono();
        double getTime();
        void reset();

    protected:
        chrono chr;
};

#endif
/*****************************************************************************/
/*****************************************************************************/
