
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
#include <timing/sleep.h>


#ifdef WIN32
#include <timing/chrono.h>
#endif

#include <logging/log.h>

#include "MultiSerial.h"

using namespace std;


MultiSerial::MultiSerial()
{

}

MultiSerial::MultiSerial(vector<string> ports_pathes, vector<int> baudrates)
{
  Connect(ports_pathes, baudrates);
}

void MultiSerial::Disconnect()
{
  if (Thread::is_alive())
		Thread::kill();
	for (auto & port : ports)
	{
		if (port)
		{
			port->disconnect();
			port = NULL;
		}
	}
	ports.clear();
}

void MultiSerial::Connect(
	vector<string> ports,
	vector<int> baudrates
	)
{

	if (ports.size() != baudrates.size())
		throw runtime_error("parameters length mismatch");

	multiserial_received.clear();
	multiserial_received.resize(ports.size());
	multiserial_sent.clear();
	multiserial_sent.resize(ports.size());

	if (Thread::is_alive())
	  {
	cout << "MultiSerial killing main thread..." << flush;
		Thread::kill();
	Thread::wait_dead();
	cout << "...done!";
	  }

	for (uint i = 0; i < ports.size(); i++)
	{
		if (ports[i] != "")
		{
			cout << "MultiSerial connecting to '" << ports[i] << "' at " << baudrates[i] << "bauds." << endl;
			auto port = new Serial(ports[i], baudrates[i]);
			this->ports.push_back(port);
			int res = port->connect2();
			if (res == -1)
				throw runtime_error("Failed to connect to port '" + ports[i] + "'");
		}
	}

	if(!Thread::is_alive())
	  {
	cout << "MultiSerial starting main thread..." << flush;
	Thread::start();
	Thread::wait_started();
	cout << "...done!" << endl;;
	  }
}

/* return how many chars were sent, -1 in case of error */
int MultiSerial::Send(int port_id, const string & data)
{
	int res = -1;
	if (port_id >= (int) ports.size())
		return -1;
//		throw runtime_error("No port with this id");
	auto & port = ports[port_id];
	BEGIN_SAFE(mutex)
		res = port->send(data);
	END_SAFE(mutex)
	  multiserial_sent[port_id] += (res >=0) ? res : 0;
	return res;
}

void MultiSerial::execute()
{
	char buffer[8192];
	/* todo use select under LINUX*/
	fd_set read_fds;

	

	while (is_alive())
	{
		int m = 0;
#ifndef WIN32
		FD_ZERO(&read_fds);
		for(unsigned int i = 0 ; i < ports.size(); i++)
		{
			auto port = ports[i];
			FD_SET(port->fd, &read_fds);
			m = max(port->fd, m);
		}	  // Wait for data to be available

		//		cout << "Multiserial performing select " << endl;
		// Set timeout
		Rhoban::chrono timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;

		auto ret =  select(m + 1, &read_fds, NULL, NULL, &timeout);
		if (ret > 0)
		{
		  //	     		cout << "Multiserial got select " << ret << endl;
			for (unsigned int i = 0; i < ports.size(); i++)
			{
				auto port = ports[i];
				//		cout << "Multiserial checking port " << i << " '" << port->deviceName << "'" << endl;
				if (FD_ISSET(port->fd, &read_fds))
				{
					int total = port->doRead(buffer, 8192);
					//				cout << "Multiserial has " << total << " on port " << i << endl;
					if(total > 0)
					{
						MultiSerialReceived(i, string(buffer, total));
						multiserial_received[i] += total;
					}
				}
			}
		}
		else if(ret < 0)
		{
		  //			cout << "Multiserial failed to perfom select " << endl;
			perror("MultiSerial");
		}
#else
		for (int i = 0; i < ports.size(); i++)
		{
			bool stalled = true;
			if (ports[i])
			{
				auto chunk = ports[i]->receive(8192);
				if (chunk.size() > 0)
				{
					stalled = false;
					MultiSerialReceived(i, chunk);
					multiserial_received[i] += chunk.size();
				}
			}
			if (stalled)
				ms_sleep(50);
		}
#endif
	}
}

MultiSerial::~MultiSerial()
{
	Disconnect();
}
