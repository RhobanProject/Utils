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
/*!\brief A Rhoban::chrono is just a type value
 *****************************************************************************/

#ifdef MSVC
#include <time.h>
#include <sys/timeb.h>

namespace Rhoban
{

	struct tttt {
		long    tv_sec;
		long    tv_usec;
	};

	typedef struct tttt chrono;
	int gettimeofday(Rhoban::chrono *tp, void *tz = NULL);
#else
#include <time.h>
#include <sys/time.h>

namespace Rhoban
{
	typedef struct timeval chrono;
#endif


	/*****************************************************************************/
	/*!\brief Reset the Rhoban::chrono
	 * \param chr the Rhoban::chrono to be resetted.
	 *****************************************************************************/
	void chrono_reset(Rhoban::chrono * chr);

	/*****************************************************************************/
	/*!\brief Create a new chono.
	 * \return the address of the Rhoban::chrono.
	 *****************************************************************************/
	Rhoban::chrono * chrono_create();

	/*****************************************************************************/
	/*!\brief kill a Rhoban::chrono and free its resources
	 *****************************************************************************/
	void delete_chrono(Rhoban::chrono * chr);

	/*****************************************************************************/
	/*!\brief Gives the number of second elapsed from the last timer reset.
	 *****************************************************************************/
	long int chrono_sec(Rhoban::chrono * chr);

	/*****************************************************************************/
	/*!\brief Gives the number of milli second elapsed from the last timer reset.
	 *****************************************************************************/
	long int chrono_msec(Rhoban::chrono * chr);

	/*****************************************************************************/
	/*!\brief Gives the number of micro second elapsed from the last timer reset.
	 *****************************************************************************/
	long int chrono_usec(Rhoban::chrono * chr);

}

class Chrono
{
    public:
        Chrono();
        double getTime();
		double getTimeMsec();
		double getTimeUsec();
		void reset();

		Chrono& operator+=(const Chrono& chr){
			this->chr.tv_sec += chr.chr.tv_sec;
			this->chr.tv_usec += chr.chr.tv_usec;
			return *this;
		}

		Chrono& operator-=(const Chrono& chr){
			if (this->chr.tv_usec < chr.chr.tv_usec)
			{
				this->chr.tv_usec += 1000000;
				this->chr.tv_sec -= 1;
			}
			if (this->chr.tv_usec < chr.chr.tv_usec)
			{
				int d = chr.chr.tv_usec / 1000000;
				this->chr.tv_usec -= d * 1000000;
				this->chr.tv_sec += d;
			}
			this->chr.tv_sec -= chr.chr.tv_sec;
			this->chr.tv_usec -= chr.chr.tv_usec;
			return *this;
		}

		// friends defined inside class body are inline and are hidden from non-ADL lookup
		friend Chrono operator+(Chrono chr,	const Chrono& rhs){	return chr += rhs;}

		// friends defined inside class body are inline and are hidden from non-ADL lookup
		friend Chrono operator-(Chrono chr, const Chrono& rhs){ return chr -= rhs; }

protected:
        Rhoban::chrono chr;
};

#endif
/*****************************************************************************/
/*****************************************************************************/
