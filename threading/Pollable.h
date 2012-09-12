#ifndef _POLLABLE_H
#define _POLLABLE_H

class Pollable
{
    public:
        virtual void poll()=0;
};

#endif // _POLLABLE_H
