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
*  Created on: 21 mars 2011
*      Author: hugo
*/

#ifndef ENCODINGS_H_
#define ENCODINGS_H_

#include <iostream>
#include "types.h"

using namespace std;

/*!
* encode and decode values to and from a buffer
*/
inline void encode_int(int value, char * buf);
inline void encode_uint(ui32 value, char * buf);
inline void encode_short(short value, char * buf);
inline void encode_ushort(unsigned short value, char * buf);

//static float double_coef = 1000.0;

inline void encode_float(float value, char * buf);


/*!
* todo: find a better encoding,
* this one  wont be properly decoded on every architecture
*/

inline ui32 decode_uint(const char * buf);
inline int decode_int(const char * buf);
inline unsigned short decode_ushort(const char * buf);
inline short decode_short(const char * buf);
inline float decode_float(const char * buf);

inline string decode_string(const char * buf);

/*!
* encode and decode values to and from a buffer
*/
inline void encode_int(int value, char * buf)
{
	//faster solution but there may be big/small endian problems
	//as well as alignment problems
	//((int *) buf)[0] = value;
	buf[0] = (char)((value & 0xff000000) >> 24);
	buf[1] = (char)((value & 0x00ff0000) >> 16);
	buf[2] = (char)((value & 0x0000ff00) >> 8);
	buf[3] = (char)((value & 0x000000ff) >> 0);
}

inline void encode_uint(ui32 value, char * buf)
{
	//faster solution but there may be big/small endian problems
	//as well as alignment problems
	//((ui32 *) buf)[0] = value;
	buf[0] = (char)((value & 0xff000000) >> 24);
	buf[1] = (char)((value & 0x00ff0000) >> 16);
	buf[2] = (char)((value & 0x0000ff00) >> 8);
	buf[3] = (char)((value & 0x000000ff) >> 0);
}

inline void encode_short(short value, char * buf)
{
	buf[0] = (char)((value & 0xff00) >> 8);
	buf[1] = (char)((value & 0x00ff) >> 0);
}

inline void encode_ushort(unsigned short value, char * buf)
{
	buf[0] = (char)((value & 0xff00) >> 8);
	buf[1] = (char)((value & 0x00ff) >> 0);
}

//static float double_coef = 1000.0;

inline void encode_float(float value, char * buf)
{
	encode_uint(*(int *)&value, buf);
	//	encode_int((int) (value * 1000), buf);
}

inline void encode_double(double value, char * buf)
{
	encode_float(value, buf);
}
/*!
* todo: find a better encoding,
* this one  wont be properly decoded on every architecture
*/

inline ui32 decode_uint(const char * buf)
{
	//return ((ui32 *) buf)[0];
	//cout << "Decoding int \t"<<((ui32 *) buf)[0]<< "\t\t("<<(int) buf[0]<<" "<< (int) buf[1]<<" "<< (int) buf[2]<<" "<< (int) buf[3]<<")"<<endl;

	ui8* buff = (ui8*)buf;
	ui32 a = buff[0] << 24;
	ui32 b = buff[1] << 16;
	ui32 c = buff[2] << 8;
	ui32 d = buff[3];
	return a | b | c | d;

	//	return  ((ui32)buf[0])<<24 | ((ui32)buf[1])<<16 | ((ui32)buf[2])<<8 | ((ui32)buf[3]);
}

inline int decode_int(const char * buf)
{
	ui8* buff = (ui8*)buf;
	ui32 a = buff[0] << 24;
	ui32 b = buff[1] << 16;
	ui32 c = buff[2] << 8;
	ui32 d = buff[3];
	return (int)(a | b | c | d);
}

inline unsigned short decode_ushort(const char * buf)
{
	ui8* buff = (ui8*)buf;
	unsigned short a = buff[0] << 8;
	unsigned short b = buff[1] << 0;
	return a | b;
}

inline short decode_short(const char * buf)
{
	ui8* buff = (ui8*)buf;
	unsigned short a = buff[0] << 8;
	unsigned short b = buff[1] << 0;
	return (short)(a | b);
}


inline float decode_float(const char * buf)
{
	//return ldexp( decode_uint(buf+1) ,(int) buf[0]-128);
	int val = decode_uint(buf);
	return *(float *)&val;
}

inline string decode_string(const char * buf)
{
	ui32 length = decode_uint(buf);
	return string(buf + 4, length);
}


#endif /* ENCODINGS_H_ */
