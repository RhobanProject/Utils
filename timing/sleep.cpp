#ifndef MSVC
#include <unistd.h>
#endif
#ifdef WIN32
#include <windows.h>
#endif

#include "sys_wait_ms.h"

void ms_sys_wait_ms(long ms)
{
#ifdef WIN32
    sys_wait_ms(ms);
#else
    usys_wait_ms(1000 * ms);
#endif
}

void us_sys_wait_ms(long us)
{
#ifdef WIN32
    sys_wait_ms(us/1000.0);
#else
    usys_wait_ms(us);
#endif
}
