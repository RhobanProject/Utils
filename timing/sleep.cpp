#ifndef MSVC
#include <unistd.h>
#endif
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "sleep.h"

#ifdef WIN32
#include <thread>
#endif

void ms_sleep(long ms) {
#ifdef WIN32
	Sleep(ms);
#else
  #ifndef DARWIN
	usleep(1000 * ms);
  #endif
#endif
}  

void ms_sys_wait_ms(long ms)
{
#ifdef WIN32
    Sleep(ms);
#else
    usleep(1000 * ms);
#endif
}

void us_sleep(long us)
{
#ifdef WIN32
	std::this_thread::sleep_for(std::chrono::microseconds(us));
#else
    usleep(us);
#endif
}
