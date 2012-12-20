#ifndef _CURVE_ENTRY_H
#define _CURVE_ENTRY_H

#include <time.h>

class CurveEntry
{
    public:
        CurveEntry(double value_, double time_);

        double time;
        double value;
};

#endif // _CURVE_ENTRY_H
