#include <unistd.h>
#ifdef WIN32
#include <windows.h>
#endif

void ms_sleep(long ms)
{
#ifdef WIN32
    Sleep(ms);
#else
    usleep(1000 * ms);
#endif
}
