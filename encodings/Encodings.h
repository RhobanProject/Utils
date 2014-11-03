/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
/*
 * encodings.h
 *
 * Created on: 21 mars 2011
 * Author: hugo
 */

#ifndef ENCODINGS_H_
#define ENCODINGS_H_

#include <iostream>
#include "types.h"

using namespace std;

typedef unsigned int uint;

namespace Rhoban{
  class Encodings{
  public:
    /*!
     * encode and decode values to and from a buffer
     */
    static void encode_int(int value, char * buf);
    static void encode_uint(ui32 value, char * buf);
    static void encode_ushort(ui16 value, char * buf);
    static void encode_float(float value, char * buf);
    static void encode_double(double value, char * buf);

    /*!
     * todo: find a better encoding,
     * this one wont be properly decoded on every architecture
     */

    static ui32 decode_uint(const char * buf){ return (ui32) (unsigned char) buf[3] | ((ui32) (unsigned char) buf[2] << 8) | ((ui32) (unsigned char) buf[1] << 16) | ((ui32) (unsigned char) buf[0] << 24) ; }
    static ui16 decode_ushort(const char * buf){ return (ui16) (unsigned char) buf[1] | ((ui16) (unsigned char) buf[0] << 8) ; }
    static int decode_int(const char * buf){ return (int) ( (ui32) (unsigned char) buf[3] | ((ui32) (unsigned char) buf[2] << 8) | ((ui32) (unsigned char) buf[1] << 16) | ((ui32) (unsigned char) buf[0] << 24));}
    static float decode_float(const char * buf);
    static double decode_double(const char * buf);
  };
}

#endif /* ENCODINGS_H_ */
