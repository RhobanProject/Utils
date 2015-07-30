/*************************************************
 * Publicly released by Rhoban System, August 2015
 *             www.rhoban.com
 *
 * Freely usable for non-commercial purposes
 *
 * Author : Hugo
 * Licence Creative Commons *CC BY-NC-SA
 * http://creativecommons.org/licenses/by-nc-sa/3.0
 *************************************************/
#ifndef UTILS_MULTISERIAL_H
#define UTILS_MULTISERIAL_H

#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>
#include <vector>

#include <threading/Thread.h>
#include <threading/Mutex.h>
#include <serial/Serial.h>

#ifdef WIN32
#include <windows.h>
#endif

#include <fstream>

using namespace std;


/* Handles asynchronous reading and writing in several serial ports */
class MultiSerial
	: private Rhoban::Thread
{
public:
	MultiSerial();
	virtual ~MultiSerial();

	//ports with empty name are ignored
	MultiSerial(
		vector<string> ports,
		vector<int> baudrates
		);

	/* called when data is received */
	virtual void MultiSerialReceived(int port, const string & data){};

	/* return how many chars were sent, -1 in case of error */
	int Send(int port_id, const string & data);

	void Disconnect();
	void Connect(
		vector<string> ports,
		vector<int> baudrates
		);

	vector<int> multiserial_received;
	vector<int> multiserial_sent;

protected:
	vector<Serial *> ports;
	void execute();
	/* prevents concurrent calls to ports */
	Rhoban::Mutex mutex;
};
#endif // UTILS_SERIAL_H
