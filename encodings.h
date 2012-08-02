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

//static float double_coef = 1000.0;

inline void encode_float(float value, char * buf);


/*!
* todo: find a better encoding,
* this one  wont be properly decoded on every architecture
*/

inline ui32 decode_uint(const char * buf);
inline int decode_int(const char * buf);
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
	buf[0] = (char) ((value & 0xff000000) >>24);
	buf[1] = (char) ((value & 0x00ff0000) >>16);
	buf[2] = (char) ((value & 0x0000ff00) >>8);
	buf[3] = (char) ((value & 0x000000ff) >>0);
}

inline void encode_uint(ui32 value, char * buf)
{
	//faster solution but there may be big/small endian problems
	//as well as alignment problems
	//((ui32 *) buf)[0] = value;
	buf[0] = (char) ((value & 0xff000000) >>24);
	buf[1] = (char) ((value & 0x00ff0000) >>16);
	buf[2] = (char) ((value & 0x0000ff00) >>8);
	buf[3] = (char) ((value & 0x000000ff) >>0);
}

//static float double_coef = 1000.0;

inline void encode_float(float value, char * buf)
{
	//Hugo: dangerous, plateform dependent
	/*
	cout <<"Encoding float \t"<< value <<" \t\t(";
	for(int j=0;j<4;j++)
	{
		ui32 n = *((ui32 *)&value);
		cout << ((n >> (j*8)) & 0xff)<<" ";
	}
	cout <<")NON!!"<<endl;
	*/
	//cout << "Dangerous: alignment and format issues"<<endl;
	//((float *) buf)[0] = value;
	//ui32 cvalue = (ui32) static_cast<int>(value*double_coef)+0x80000000;
	/*
	buf[0] = (char) ((cvalue & 0xff000000) >>24);
		buf[1] = (char) ((cvalue & 0x00ff0000) >>16);
		buf[2] = (char) ((cvalue & 0x0000ff00) >>8);
		buf[3] = (char) ((cvalue & 0x000000ff) >>0);
	encode_uint(cvalue,buf);*/
	encode_int((int) (value * 1000), buf);
}

inline void encode_double(double value, char * buf)
{
	encode_int((int) (value * 1000), buf);
}
/*!
* todo: find a better encoding,
* this one  wont be properly decoded on every architecture
*/

inline ui32 decode_uint(const char * buf)
{
	//return ((ui32 *) buf)[0];
	//cout << "Decoding int \t"<<((ui32 *) buf)[0]<< "\t\t("<<(int) buf[0]<<" "<< (int) buf[1]<<" "<< (int) buf[2]<<" "<< (int) buf[3]<<")"<<endl;

	ui8* buff = (ui8*) buf;
	ui32 a = buff[0]<<24;
	ui32 b = buff[1]<<16;
	ui32 c = buff[2]<<8;
	ui32 d = buff[3];
	return a | b | c |d;

	//	return  ((ui32)buf[0])<<24 | ((ui32)buf[1])<<16 | ((ui32)buf[2])<<8 | ((ui32)buf[3]);
}

inline int decode_int(const char * buf)
{
	//return ((ui32 *) buf)[0];
	//cout << "Decoding int \t"<<((ui32 *) buf)[0]<< "\t\t("<<(int) buf[0]<<" "<< (int) buf[1]<<" "<< (int) buf[2]<<" "<< (int) buf[3]<<")"<<endl;

	ui8* buff = (ui8*) buf;
	ui32 a = buff[0]<<24;
	ui32 b = buff[1]<<16;
	ui32 c = buff[2]<<8;
	ui32 d = buff[3];
	return (int) (a | b | c |d);

	//	return  ((ui32)buf[0])<<24 | ((ui32)buf[1])<<16 | ((ui32)buf[2])<<8 | ((ui32)buf[3]);
}


inline float decode_float(const char * buf)
{
	//return ldexp( decode_uint(buf+1) ,(int) buf[0]-128);
	//Hugo: dangerous, plateform dependent
	//cout << "Decoding float \t"<< ((float *) buf)[0]<< "\t\t("<<(int) buf[0]<<" "<< (int) buf[1]<<" "<< (int) buf[2]<<" "<< (int) buf[3]<<")"<<endl;
	//cout << "Dangerous: alignment and format issues"<<endl;
	//return ((float *) buf)[0];
	//return (static_cast<float>(decode_uint(buf)) -0x80000000)/ double_coef;
	return decode_int(buf)/1000.0;
}

inline string decode_string(const char * buf)
{
	ui32 length = decode_uint(buf);
	return string(buf+4,length);
}


#endif /* ENCODINGS_H_ */
