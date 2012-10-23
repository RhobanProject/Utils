/*************************************************
 * Publicly released by Rhoban System, August 2012
 *             www.rhoban-system.fr
 *
 * Freely usable for non-commercial purposes
 *
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string.h>

#include <ticks.h>

#ifdef LINUX
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#endif

#ifdef MACOSX
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <serial.h>
#endif

#include <logging/log.h>

#include "Serial.h"

using namespace std;

Serial::Serial(string deviceName, int deviceBaudrate): handle(0), recording(false), recorded("")
{
	setDevice(deviceName);
	this->deviceBaudrate = deviceBaudrate;
}


void Serial::setRts(int value)
{
#if defined(LINUX) || defined(ROBOARD)
	int cmd;

	ioctl(fd, TIOCMGET, &cmd);
	if (value) {
		cmd |= TIOCM_RTS;
	} else {
		cmd &= ~ TIOCM_RTS;
	}
	ioctl(fd, TIOCMSET, &cmd);
#endif
}

void Serial::fdClose()
{
#ifndef WIN32
	if (fd != -1) {
		close(fd);
	}

	fd = -1;
#endif
}

/**
 * Initializes the usart device
 */
int Serial::connect()
{
#ifdef WIN32

	DCB Dcb;
	COMMTIMEOUTS Timeouts;
	DWORD dwError;

	// Open serial device
	handle = CreateFile(deviceName.c_str(), GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, NULL );

	if( handle == INVALID_HANDLE_VALUE ) {
		goto USART_INIT_ERROR;
	}

	// Setting communication property
	Dcb.DCBlength = sizeof(DCB);

	if( GetCommState( handle, &Dcb ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	// Set baudrate
	Dcb.BaudRate                        = (DWORD)deviceBaudrate;
	Dcb.ByteSize                        = 8;                                    // Data bit = 8bit
	Dcb.Parity                          = NOPARITY;                             // No parity
	Dcb.StopBits                        = ONESTOPBIT;                   // Stop bit = 1
	Dcb.fParity                         = NOPARITY;                             // No Parity check
	Dcb.fBinary                         = 1;                                    // Binary mode
	Dcb.fNull                           = 0;                                    // Get Null byte
	Dcb.fAbortOnError           		= 1;
	Dcb.fErrorChar                      = 0;

	// Not using XOn/XOff
	Dcb.fOutX                           = 0;
	Dcb.fInX                            = 0;

	// Not using H/W flow control
	Dcb.fDtrControl                     = DTR_CONTROL_DISABLE;
	Dcb.fRtsControl                     = RTS_CONTROL_DISABLE;
	Dcb.fDsrSensitivity         = 0;
	Dcb.fOutxDsrFlow            = 0;
	Dcb.fOutxCtsFlow            = 0;

	if( SetCommState(handle, &Dcb) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	if( SetCommMask( handle, 0 ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	if( SetupComm(handle, 4096, 4096 ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	if( PurgeComm( handle, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	if( ClearCommError( handle, &dwError, NULL ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	if( GetCommTimeouts( handle, &Timeouts ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	Timeouts.ReadIntervalTimeout = 1;
	Timeouts.ReadTotalTimeoutMultiplier = 0;
	Timeouts.ReadTotalTimeoutConstant = 1; // must not be zero.
	Timeouts.WriteTotalTimeoutMultiplier = 0;
	Timeouts.WriteTotalTimeoutConstant = 0;

	if( SetCommTimeouts( handle, &Timeouts ) == FALSE ) {
		goto USART_INIT_ERROR;
	}

	return 0;

	USART_INIT_ERROR:
	return -1;
#elif LINUX
	struct termios newtio;
	struct serial_struct serinfo;

	memset(&newtio, 0, sizeof(newtio));

	if((fd = open(deviceName.c_str(), O_RDWR|O_NOCTTY|O_NONBLOCK)) < 0) {
		cerr << "device open error: " << deviceName << endl;
		goto USART_INIT_ERROR;
	}

	newtio.c_cflag              = B38400|CS8|CLOCAL|CREAD;
	newtio.c_iflag              = IGNPAR;
	newtio.c_oflag              = 0;
	newtio.c_lflag              = 0;
	newtio.c_cc[VTIME]  = 0;    // time-out ê°’ (TIME * 0.1ì´ˆ) 0 : disable
	newtio.c_cc[VMIN]   = 0;    // MIN ì�€ read ê°€ return ë�˜ê¸° ìœ„í•œ ìµœì†Œ ë¬¸ìž� ê°œìˆ˜

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	if (fd == -1) {
		goto USART_INIT_ERROR;
	}

	if (ioctl(fd, TIOCGSERIAL, &serinfo) < 0) {
		fprintf(stderr, "Cannot get serial info\n");
		goto USART_INIT_ERROR;
	}

	serinfo.flags &= ~ASYNC_SPD_MASK;
	serinfo.flags |= ASYNC_SPD_CUST;
	serinfo.custom_divisor = serinfo.baud_base / (float)deviceBaudrate;

	if(ioctl(fd, TIOCSSERIAL, &serinfo) < 0) {
		fprintf(stderr, "Cannot set serial info\n");
		goto USART_INIT_ERROR;
	}

	fdClose();

	if((fd = open(deviceName.c_str(), O_RDWR|O_NOCTTY|O_NONBLOCK)) < 0) {
		cerr << "device open error: " << deviceName << endl;
		goto USART_INIT_ERROR;
	}

	newtio.c_cflag = B38400|CS8|CLOCAL|CREAD;
	newtio.c_iflag = IGNPAR;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN]   = 0;

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);

	return 0;

	USART_INIT_ERROR:
	fdClose();
	return -1;
#endif
}

/**
 * Closes the device
 */
void Serial::disconnect()
{
#ifdef WIN32
	if(handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(handle);
		handle = INVALID_HANDLE_VALUE;
	}
#else
	fdClose();
#endif
}

void Serial::setDevice(string name)
{
#ifdef WIN32
	if(name != "" && name[0] != '\\')
		name = "\\\\.\\" + name;
#endif
	deviceName = name;
}

/**
 * Changes the channel speed
 */
void Serial::setSpeed(int baudrate)
{
#ifdef WIN32
	fprintf(stderr, "usart_set_channel_speed not implemented for WIN32\n");
#elif LINUX
	struct serial_struct serinfo;

	if (fd == -1) {
		return;
	}

	if(ioctl(fd, TIOCGSERIAL, &serinfo) < 0) {
		fprintf(stderr, "Cannot get serial info\n");
		return;
	}

	serinfo.flags &= ~ASYNC_SPD_MASK;
	serinfo.flags |= ASYNC_SPD_CUST;
	serinfo.custom_divisor = serinfo.baud_base / baudrate;

	if(ioctl(fd, TIOCSSERIAL, &serinfo) < 0) {
		fprintf(stderr, "Cannot set serial info\n");
		return;
	}
#endif
}


/**
 * Reads
 */
size_t Serial::receive(char *destination, size_t size)
{
	int n = 0;

#ifdef WIN32
	DWORD dwToRead, dwRead;
#endif

	if (size > 0) {
#ifdef WIN32

		dwToRead = (DWORD)size;
		dwRead = 0;

		FlushFileBuffers(handle);

		if( ReadFile(handle, destination, dwToRead, &dwRead, NULL ) == FALSE ) {
			DWORD error_code = GetLastError();
			cerr << "Com Port Error " << error_code << endl;
			return 0;
		}
		n = dwRead;

#else
		n = read(fd, destination, size);
#endif
		if(recording && n>0)
			recorded += "Received: " + string(destination, n) + "\n";
	}

	return n;
}

string Serial::receive(size_t size)
{
	char result[size];
	int nb = receive(result, size);
	return string(result, nb);
}

char Serial::receiveChar()
{
	char result;
	int nb = receive(&result,1);
	if(nb != 1)
		throw string("Failed to read one char from device " + deviceName);
	return result;
}

/*
 * reads one short
 */
short Serial::receiveShort()
{
	return receiveChar() | (receiveChar() << 8) ;
}

int Serial::receiveInt()
{
	return  receiveChar() | (receiveChar() << 8) |  (receiveChar() << 16) | (receiveChar() << 24);
}

/**
 * Flushes
 */
void Serial::flush()
{
#ifdef WIN32
	FlushFileBuffers(handle);
	PurgeComm(handle, PURGE_RXABORT|PURGE_RXCLEAR);
#endif
}

/**
 * Sends
 */
size_t Serial::send(string data)
{
	return send(data.c_str(), data.size());
}

size_t Serial::send(const char *data, size_t size)
{
	size_t got;

#ifdef WIN32
	DWORD dwToWrite, dwWritten;

	dwToWrite = (DWORD)size;
	dwWritten = 0;

	WriteFile(handle, data, dwToWrite, &dwWritten, NULL);
	got = dwWritten;
	FlushFileBuffers(handle);
#else
#ifdef ROBOARD
	setRts(1);
#endif
	got = write(fd, data, size);
#ifdef ROBOARD
	setRts(0);
#endif
#endif

	if(recording)
		recorded += "Sent: " + string(data, got) + "\n";

	return got;
}

void Serial::seekPattern(string pattern, int max_chars_wait)
{
	string buf = "";
	while(buf.size() < pattern.size())
	try
	{
			char c = receiveChar();
			buf += c ;
	}
	catch(...)//(string exc)
	{
		//cerr << "Problem while seeking pattern " << exc << endl;
		syst_wait_ms(100);
	}

	int to_wait = 0;

	while(buf != pattern)
	{
		char c = receiveChar();
		buf = buf.substr(1,buf.size() - 1) + c;
		if(to_wait ++ >= max_chars_wait)
		{
			cerr << "seek_pattern: waited too long (" << max_chars_wait << ") for pattern" << endl;
			throw string("seek_pattern: waited too long for pattern");
		}
		//cerr << (int) c << " ";
	}
	if(to_wait >0)
		cerr << "seek_pattern: thrown " << to_wait << "chars to garbage" << endl;
	cerr << endl;
}

