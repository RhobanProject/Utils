#ifndef HIGHRESCLOCKH
#define HIGHRESCLOCKH

#ifdef WIN32

#include <Windows.h>
#include <chrono>

struct HighResClock
{
	typedef long long                               rep;
	typedef std::nano                               period;
	typedef std::chrono::duration<rep, period>      duration;
	typedef std::chrono::time_point<HighResClock>   time_point;
	static const bool is_steady = true;

	static time_point now();
};

#endif

#endif