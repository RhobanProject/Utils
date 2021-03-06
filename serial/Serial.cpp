
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

#include <timing/sleep.h>
#ifdef MSVC
#undef LINUX
#endif 

#ifdef LINUX
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <linux/serial.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

#ifdef MACOSX
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <serial.h>
#endif

#include <timing/chrono.h>

#include <logging/log.h>

#include "Serial.h"

using namespace std;

Serial::Serial(string deviceName, int deviceBaudrate): fd(0), record_stream(""), recording(false)
{
	if (deviceBaudrate == -1)
		setFileDevice(deviceName);
	else
		setDevice(deviceName);
	this->deviceBaudrate = deviceBaudrate;
}


Serial::~Serial()
{
	if(recording)
          record_stream.close();
	recording = false;
	if (IsOpen())
		disconnect();
}

bool Serial::IsOpen()
{
  return (fd  > 0);
}

void Serial::setRts(int value)
{
#ifndef WIN32
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

}

/**
 * Initializes the usart device
 */
int Serial::connect(bool blocking)
{
	if(device_is_file)
	{
#ifdef WIN32
		fd = CreateFile(deviceName.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(fd == INVALID_HANDLE_VALUE)
		  return -1;
#else
		fd = open(deviceName.c_str(), O_RDONLY);
		if(fd == -1 || fd==0)
			return -1;
#endif
	}
	else
	{
#ifdef WIN32
		DCB Dcb;
		DWORD dwError;

		// Open serial device
		fd = CreateFile(
			deviceName.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			0, //dont share the port
			NULL, //no security
			OPEN_EXISTING,
			FILE_FLAG_WRITE_THROUGH,// | FILE_FLAG_OVERLAPPED,
			NULL);

		if( fd == INVALID_HANDLE_VALUE ) {
			goto USART_INIT_ERROR;
		}

		// Setting communication property
		Dcb.DCBlength = sizeof(DCB);

		if( GetCommState( fd, &Dcb ) == FALSE ) {
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

		if( SetCommState(fd, &Dcb) == FALSE )
			goto USART_INIT_ERROR;

		if( SetCommMask( fd, 0 ) == FALSE )
			goto USART_INIT_ERROR;

		if( SetupComm(fd, 4096, 4096 ) == FALSE )
			goto USART_INIT_ERROR;

		if( PurgeComm( fd, PURGE_TXABORT|PURGE_TXCLEAR|PURGE_RXABORT|PURGE_RXCLEAR ) == FALSE )
			goto USART_INIT_ERROR;

		if( ClearCommError( fd, &dwError, NULL ) == FALSE )
			goto USART_INIT_ERROR;

		if( GetCommTimeouts( fd, &Timeouts ) == FALSE )
			goto USART_INIT_ERROR;

		/* from http://msdn.microsoft.com/en-us/library/windows/desktop/aa363190%28v=vs.85%29.aspx
		 * If an application sets ReadIntervalTimeout and ReadTotalTimeoutMultiplier to MAXDWORD and sets ReadTotalTimeoutConstant to a value 
		 * greater than zero and less than MAXDWORD, one of the following occurs when the ReadFile function is called:
                 * If there are any bytes in the input buffer, ReadFile returns immediately with the bytes in the buffer.
                 * If there are no bytes in the input buffer, ReadFile waits until a byte arrives and then returns immediately.
                 * If no bytes arrive within the time specified by ReadTotalTimeoutConstant, ReadFile times out. 
				 */
		Timeouts.ReadIntervalTimeout = MAXDWORD;
		Timeouts.ReadTotalTimeoutMultiplier = 0;
		Timeouts.ReadTotalTimeoutConstant = 0;
		Timeouts.WriteTotalTimeoutMultiplier = 0;
		Timeouts.WriteTotalTimeoutConstant = 0;

		if( SetCommTimeouts( fd, &Timeouts ) == FALSE )
			goto USART_INIT_ERROR;

		return 0;

		USART_INIT_ERROR:
		return -1;
#else
                int flags;
		struct termios newtio;

                flags = O_RDWR|O_NOCTTY;

                if (!blocking) {
                    flags |= O_NONBLOCK;
                }

		memset(&newtio, 0, sizeof(newtio));

		if((fd = open(deviceName.c_str(), flags)) < 0) {
			cerr << "Failed to open serial device: " << deviceName << endl;
			perror("");
			goto USART_INIT_ERROR;
		}

		newtio.c_cflag              = B38400|CS8|CLOCAL|CREAD;
		newtio.c_iflag              = IGNPAR;
		newtio.c_oflag              = 0;
		newtio.c_lflag              = 0;
		newtio.c_cc[VTIME]  = 0;    // time-out ê°’ (TIME * 0.1ì´ˆ) 0 : disable
		newtio.c_cc[VMIN]   = blocking ? 1 : 0;    // MIN ì�€ read ê°€ return ë�˜ê¸° ìœ„í•œ ìµœì†Œ ë¬¸ìž� ê°œìˆ˜

		tcflush(fd, TCIFLUSH);
		tcsetattr(fd, TCSANOW, &newtio);
                
		if (fd == -1) {
			goto USART_INIT_ERROR;
		}
                
                setSpeed(deviceBaudrate);

		fdClose();

		if((fd = open(deviceName.c_str(), flags)) < 0) {
			cerr << "Second device open error (after setting: " << deviceName << endl;
			goto USART_INIT_ERROR;
		}

  
#ifdef LINUX
                newtio.c_cflag = B38400|CS8|CLOCAL|CREAD;
#elif MACOSX
                tcgetattr(fd, &newtio);
                cfsetispeed(&newtio,B115200);
                cfsetospeed(&newtio,B115200);                
                newtio.c_cflag |= CLOCAL | CREAD | CS8; 
                newtio.c_cflag &= ~PARENB; 
                newtio.c_cflag &= ~CSTOPB; 
                newtio.c_cflag &= ~CSIZE; 
#endif
                newtio.c_iflag = IGNPAR;
                newtio.c_oflag = 0;
                newtio.c_lflag = 0;
                newtio.c_cc[VTIME]  = 0;
                newtio.c_cc[VMIN]   = blocking ? 1 : 0;
  
		tcflush(fd, TCIFLUSH);
		tcsetattr(fd, TCSANOW, &newtio);
                
                setSpeed(deviceBaudrate);
                
		return 0;

		USART_INIT_ERROR:
		fdClose();
		return -1;
#endif
	}
	return 0;
}

/* returns the file descriptor */
int Serial::get_fd()
{
	return (int) fd;
}

/**
* Initializes the usart device
*/
int Serial::connect2()
{
#ifdef WIN32
	connect();
#else
	struct termios tio;
	int flags;
	memset(&tio, 0, sizeof(tio));

	if ((fd = open(deviceName.c_str(), O_RDWR | O_NONBLOCK |O_NOCTTY)) == -1){
		printf("Error while opening\n"); // Just if you want user interface error control
		return -1;
	}

	if((tcgetattr(fd, &tio) == -1))
	  goto error;


	tio.c_lflag = 0;
	tio.c_oflag = 0;
	tio.c_cflag = (tio.c_cflag & ~CSIZE) | CS8 | B57600;           // 8n1, see termios.h for more information

	tio.c_cc[VMIN] = 0;
	tio.c_cc[VTIME] = 5;

	tio.c_iflag &= ~IGNBRK & ~IGNCR & ~ICRNL & ~INLCR;//dont mess up with carriage return
	tio.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl
	tio.c_cflag |= (CLOCAL | CREAD);

	tio.c_cflag &= ~(PARENB | PARODD);  
	tio.c_cflag &= ~CSTOPB;
        tio.c_cflag &= ~CRTSCTS;

	tcflush(fd, TCIFLUSH);
	if (tcsetattr (fd, TCSANOW, &tio) != 0)
	  goto error;

	int baudrate_code;
	switch (deviceBaudrate) {
	case 1200: baudrate_code = B1200; break;
	case 1800: baudrate_code = B1800; break;
	case 2400: baudrate_code = B2400; break;
	case 4800: baudrate_code = B4800; break;
	case 9600: baudrate_code = B9600; break;
	case 19200: baudrate_code = B19200; break;
	case 38400: baudrate_code = B38400; break;
	case 57600: baudrate_code = B57600; break;
	case 115200: baudrate_code = B115200; break;
	case 230400: baudrate_code = B230400; break;
	case 460800: baudrate_code = B460800; break;
	case 500000: baudrate_code = B500000; break;
	case 576000: baudrate_code = B576000; break;
	case 921600: baudrate_code = B921600; break;
	case 1000000: baudrate_code = B1000000; break;
	case 1152000: baudrate_code = B1152000; break;
	case 1500000: baudrate_code = B1500000; break;
	case 2000000: baudrate_code = B2000000; break;
	case 2500000: baudrate_code = B2500000; break;
	case 3000000: baudrate_code = B3000000; break;
	case 3500000: baudrate_code = B3500000; break;
	case 4000000: baudrate_code = B4000000; break;
	default:
	  throw runtime_error("Serial::setSpeed: unknown baudrate");
	}
	tcflush(fd, TCIFLUSH);
	if(
	   (cfsetospeed(&tio, baudrate_code) == -1)
	   || (cfsetispeed(&tio, baudrate_code) == -1)
	   || (tcsetattr(fd, TCSANOW, &tio) == -1)
	  )
	  goto error;

#endif
	return 0;
error:
#ifndef WIN32
	    perror("Error setting serial baudrate");
	    close(fd);
#endif
	return -1;
}

/**
 * Closes the device
 */
void Serial::disconnect()
{
#ifdef WIN32
	if(fd > 0)
		CloseHandle(fd);
	fd = 0;
#else
close(fd);
fd = -1;
#endif
}

void Serial::setDevice(string name)
{
#ifdef WIN32
	if(name != "" && name[0] != '\\')
		name = "\\\\.\\" + name;
#endif
	deviceName = name;
	device_is_file = false;
}

void Serial::setFileDevice(string name)
{
	deviceName = name;
	device_is_file = true;
}

int Serial::getSpeed()
{
    return deviceBaudrate;
}

/**
 * Changes the channel speed
 */
void Serial::setSpeed(int baudrate)
{
#ifdef WIN32
	cout << "Changing serial speed of port " << deviceName << " from " << deviceBaudrate << " to " << baudrate << "..." << endl;
	bool isConnected = IsOpen();
	if (isConnected)
	{
		cout << " disconnecting..." << std::flush;
		disconnect();
	}
	ms_sleep(1000);
	deviceBaudrate = baudrate;
	if (isConnected)
	{
		cout << "reconnecting..." << std::flush;
		connect();
		cout << "done" << endl;
	}
#elif LINUX
        struct serial_struct serinfo;

	if (fd == -1) {
		return;
	}

        if (ioctl(fd, TIOCGSERIAL, &serinfo) >= 0) {
            serinfo.flags &= ~ASYNC_SPD_MASK;
            serinfo.flags |= ASYNC_SPD_CUST;
            serinfo.flags |= ASYNC_LOW_LATENCY;
            serinfo.custom_divisor = serinfo.baud_base / baudrate;

            ioctl(fd, TIOCSSERIAL, &serinfo);
	    tcflush(fd, TCIFLUSH);
        } else { 	
            struct termios newtio;
            tcgetattr(fd, &newtio);
            int baudrate_code;
            switch (baudrate) {
                case 1200: baudrate_code = B1200; break;
                case 1800: baudrate_code = B1800; break;
                case 2400: baudrate_code = B2400; break;
                case 9600: baudrate_code = B9600; break;
                case 19200: baudrate_code = B19200; break;
                case 38400: baudrate_code = B38400; break;
                case 57600: baudrate_code = B57600; break;
                case 115200: baudrate_code = B115200; break;
                case 230400: baudrate_code = B230400; break;
                case 460800: baudrate_code = B460800; break; 
                case 500000: baudrate_code = B500000; break; 
                case 576000: baudrate_code = B576000; break; 
                case 921600: baudrate_code = B921600; break; 
                case 1000000: baudrate_code = B1000000; break; 
                case 1152000: baudrate_code = B1152000; break; 
                case 1500000: baudrate_code = B1500000; break; 
                case 2000000: baudrate_code = B2000000; break; 
                case 2500000: baudrate_code = B2500000; break; 
                case 3000000: baudrate_code = B3000000; break; 
                case 3500000: baudrate_code = B3500000; break; 
                case 4000000: baudrate_code = B4000000; break; 
                default:
                  throw "Serial::setSpeed: unknown baudrate"; 
            }
            cfsetispeed(&newtio, baudrate_code);
            cfsetospeed(&newtio, baudrate_code);
            tcsetattr(fd, TCSANOW, &newtio);
        }
#elif MACOSX
        
        int baudrate_code;
        switch (baudrate) {
        case 1200: baudrate_code = B1200; break;
        case 1800: baudrate_code = B1800; break;
        case 2400: baudrate_code = B2400; break;
        case 9600: baudrate_code = B9600; break;
        case 19200: baudrate_code = B19200; break;
        case 38400: baudrate_code = B38400; break;
        case 57600: baudrate_code = B57600; break;
        case 115200: baudrate_code = B115200; break;
        case 230400: baudrate_code = B230400; break;
        default:
          throw "Serial::setSpeed: unknown baudrate"; 
        }
 
        struct termios tio;
        cfmakeraw(&tio);
        cfsetispeed(&tio,baudrate_code);
        cfsetospeed(&tio,baudrate_code);
        tcsetattr(fd, TCSANOW, &tio);  
#endif
        deviceBaudrate = baudrate;
}

bool Serial::waitForData(int timeout_us)
{
#ifdef WIN32
	return true;
#else
    if(fd > 0)
      {
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

		// Set timeout 
		Rhoban::chrono timeout;
		timeout.tv_sec = timeout_us/1000000;
		timeout.tv_usec = timeout_us%1000000;

		// Wait for data to be available
		return select(fd + 1, &read_fds, NULL, NULL, &timeout) > 0;
}
    else{
      usleep(timeout_us);
      return false;
    }
#endif
}

/**
 * Read data with some timeout
 */
size_t Serial::readTimeout(char *destination, size_t size, int timeout_us)
{
#ifdef WIN32
    DWORD dwBytesRead;

    Timeouts.ReadTotalTimeoutConstant = timeout_us/1000;
    if (!SetCommTimeouts(fd, &Timeouts)) {
        return 0;
    }
    if (!ReadFile(fd , destination, size, &dwBytesRead, NULL))  {
        return 0;
    }

    return dwBytesRead;
#else
    char sret;
    size_t readed = 0;

    // Initialize file descriptor sets
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    // Set timeout 
    Rhoban::chrono timeout;
    timeout.tv_sec = timeout_us/1000000;
    timeout.tv_usec = timeout_us%1000000;

    // cout << "Entering select..." << endl;

    // Wait for data to be available
    while (readed < size && (sret=select(fd + 1, &read_fds, NULL, NULL, &timeout)) > 0) {
        size_t ret = doRead(destination+readed, size-readed);

        if (ret > 0) {
            readed += ret;
        }
    
        FD_ZERO(&read_fds);
        FD_SET(fd, &read_fds);
    }

    return readed;
#endif
}

/**
 * Read data from the port directly
 */
int Serial::doRead(char *destination, size_t size)
{
#ifdef WIN32
	DWORD dwRead;
    ReadFile(fd, destination, size, &dwRead, NULL );
    return dwRead;
#else
   return read(fd, destination, size);
#endif
}


/**
 * Reads
 */
size_t Serial::receive(char *destination, size_t size, bool blocking)
{
	if (!IsOpen())
	{
		string err = "Cannot read from serial port: disconnected";
		if (blocking)
			throw runtime_error(err);
		else
		{
			cerr << err << endl;
			ms_sleep(1000);
			return -1;
		}
	}

	size_t total = 0;
	//cout << "Receiving " << size << " bytes, blocking " << blocking << endl;

#ifdef WIN32
	DWORD dwToRead, dwRead;
#endif

	while (total < size) {
#ifdef WIN32

		dwToRead = (DWORD)(size - total);
		dwRead = 0;

		if( ReadFile(fd, destination +  total, dwToRead, &dwRead, NULL ) == FALSE ) {
			DWORD error_code = GetLastError();
			if (error_code != CE_OVERRUN)
			{
				string err = "Serial Port Error " + to_string(error_code);
				if (blocking)
					throw runtime_error("Failed to read from serial port:\n\t" + err);
				else
				{
					cerr << err << endl;
					dwRead = 0;
				}
			}
		}
		int n = dwRead;
#else
		int n = read(fd, destination, size);
#endif
		if(recording && n>0)
			record_stream << string(destination, n);
		total += n;
		//if(total < size)
			//cout << "Receiving " << size << " got total " << total << " this loop " << n << " blocking " << (blocking ? 1 : 0) << endl;
		if(!blocking) break;
		if(n==0)
		{
			//cout << "Received nothing waiting 50 ms" << endl;
			ms_sleep(10);
		}
	}
	return total;
}

string Serial::receive(size_t size, bool blocking)
{
	char * result = (char *) malloc(size);
	int nb = receive(result, size, blocking);
	if(nb < 0 && errno != EAGAIN)
	  {
	    cout<< "Failed to receive data on port " + deviceName << " error " << errno << endl;
	    perror("Error");
	  }
	string res = string(result, (nb >= 0) ? nb : 0);
	free(result);
	
        return res;
}

char Serial::receiveChar()
{
	char result;
	int nb = receive(&result,1, true);
	if(nb < 0)
		throw runtime_error("Error when waiting char from device " + deviceName);
	else if(nb == 0)
		throw runtime_error("No char received from device " + deviceName);
	else
		return result;
}

/*
 * reads one short
 */
unsigned short Serial::receiveShort()
{
	char b[2];
	receive(b,2, true);
	return ((unsigned char) b[0]) | (((unsigned char) b[1]) << 8) ;
}

int Serial::receiveInt()
{
	char b[4];
	receive(b,4, true);
	return (unsigned char) b[0] | ((unsigned char) b[1] << 8) | ((unsigned char) b[2] << 16) | ((unsigned char) b[3] << 24);
	//return  receiveChar() | (receiveChar() << 8) |  (receiveChar() << 16) | (receiveChar() << 24);
}

/**
 * Flushes
 */
void Serial::flush()
{
#ifdef WIN32
	FlushFileBuffers(fd);
	PurgeComm(fd, PURGE_RXABORT|PURGE_RXCLEAR);
#else
        tcflush(fd, TCIFLUSH);
#endif
}

/**
 * Sends
 */
size_t Serial::send(const string & data, bool blocking)
{
	return send(data.c_str(), data.size(), blocking);
}

size_t Serial::doSend(const char *data, size_t size)
{
	size_t got = 0;

#ifdef WIN32
	DWORD dwToWrite = (DWORD)size;
        DWORD dwWritten = 0;
        //cout << "Sending " << dwToWrite - got << " bytes " << endl;
        WriteFile(fd, data + got, dwToWrite - got, &dwWritten, NULL);
        got += dwWritten;
        //cout << "Sent " << got <<"/" << size <<  endl;
	FlushFileBuffers(fd);
#else
#ifdef ROBOARD
	setRts(1);
#endif
	got = write(fd, data, size);
#ifdef ROBOARD
	setRts(0);
#endif
#endif
	return got;
}

size_t Serial::send(const char *data, size_t size, bool blocking)
{


	if(device_is_file)
	{
		ms_sleep(1 + size / 50);
		return size;
	}
	else if(!IsOpen())
	  {
	    cout << "Cannot send, port is closed" << endl;
	    return 0;
	  }


	size_t got = 0;

#ifdef WIN32
	DWORD dwToWrite = (DWORD)size;
	int max_tries = 100;
	while(got < size && max_tries-->0)
	{
		int sent = doSend(data, size);
		if (sent < 0)
			return sent;
		else if (sent == 0)
			Sleep(10);
		else
			got += sent;
		if (!blocking)
			break;
	}
	FlushFileBuffers(fd);
#else
#ifdef ROBOARD
	setRts(1);
#endif
	got = write(fd, data, size);
#ifdef ROBOARD
	setRts(0);
#endif
#endif

	return got;
}

void Serial::seekPattern(string pattern, int max_chars_wait)
{
	int to_wait = 0;
	string buf = "";
	while(buf != pattern)
	{
		char c = receiveChar();
		buf +=c;
		if (buf.size() > pattern.size())
		{
			buf = buf.substr(buf.size() - pattern.size(), buf.size() - 1);
			if (to_wait++ >= max_chars_wait)
			{
				cerr << "seek_pattern: waited too long (" << max_chars_wait;
				cout << ") for pattern" << endl;
				disconnect();
				throw runtime_error("seek_pattern: waited too long for pattern, closing port");
			}
		}
	}
	if(to_wait >0)
		cerr << "seek_pattern: thrown " << to_wait << "chars to garbage" << endl;
}

void Serial::record(string filename)
{
	record_stream.open(filename.c_str());
	if(record_stream.is_open())
		recording = true;
	else
		throw string("Failed to open serial log file ") + filename;
}

