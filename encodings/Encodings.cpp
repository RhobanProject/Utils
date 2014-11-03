/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <iostream>
#include <stdio.h>
#ifdef WIN32
#ifndef MSVC
#include <windows.h>
#endif
#else
#include <arpa/inet.h>
#endif
#include "Encodings.h"

using namespace std;

namespace Rhoban
{
    union floatAndInt
    {
        float floatValue;
        ui32 intValue;
    };

    void Encodings::encode_int(int value, char * buf)
    {
    	buf[0] = (value & 0xFF000000) >> 24;
    	buf[1] = (value & 0x00FF0000) >> 16;
    	buf[2] = (value & 0x0000FF00) >> 8;
    	buf[3] = (value & 0x000000FF) >> 0;
    }

    void Encodings::encode_uint(ui32 value, char * buf)
    {
    	buf[0] = (value & 0xFF000000) >> 24;
    	buf[1] = (value & 0x00FF0000) >> 16;
    	buf[2] = (value & 0x0000FF00) >> 8;
    	buf[3] = (value & 0x000000FF) >> 0;
    }

    void Encodings::encode_ushort(ui16 value, char * buf)
    {
    	buf[0] = (value & 0xFF00) >> 8;
    	buf[1] = (value & 0x00FF) >> 0;
    }

    void Encodings::encode_float(float value, char * buf)
    {
        encode_uint(*(int *)&value, buf);
    }

    void Encodings::encode_double(double value, char * buf)
    {
        encode_float((float)value, buf);
    }

    float Encodings::decode_float(const char * buf)
    {
        int val = decode_uint(buf);
        return *(float *)&val;
    }

    double Encodings::decode_double(const char * buf)
    {
        return((double)decode_float(buf));
    }
}
