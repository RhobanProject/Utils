#include <iostream>

#ifndef DARWIN
#include <sys/types.h>

#ifndef MSVC
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <linux/if.h>
#else
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0
#endif
#endif
#include <errno.h>
#include <string.h>

#include "UDPBroadcast.hpp"

namespace Rhoban {

UDPBroadcast::UDPBroadcast(int port)
{
#ifdef MSVC
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    _port = port;

    //Network initialization
    _readFd = -1;
    _writeFd = -1;
    openRead();
    openWrite();
    retrieveBroadcastAddress();
}

UDPBroadcast::~UDPBroadcast()
{
    closeWrite();
    closeRead();
}

void UDPBroadcast::openRead()
{
    //Close current connection if open
    closeRead();

    //Open read socket
    _readFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_readFd == -1) {
        std::cout << 
            "ERROR: UDPBroadcast: Unable to open read socket" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return;
    }

    //Bind socoket to listening port
    SOCKADDR_IN addr;
#ifndef MSVC
    bzero(&addr, sizeof(addr));
#else
	unsigned long ul = 1; 
	int nRet = ioctlsocket(_readFd, FIONBIO, (unsigned long *)&ul);
	if (nRet == SOCKET_ERROR)
		std::cerr << "Failed to put socket in non-bloking mode..." << std::endl;
	ZeroMemory(&addr, sizeof(addr));
#endif
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int error = bind(_readFd, (SOCKADDR*)&addr, sizeof(addr));
    if (error == -1) {
        std::cout << 
            "ERROR: UDPBroadcast: Unable to bind read socket" << std::endl;
        std::cout << strerror(errno) << std::endl;
        closeRead();
        return;
    }
}
void UDPBroadcast::openWrite()
{
    //Close current connection if open
    closeWrite();

    //Open read socket
    _writeFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_writeFd == -1) {
        std::cout << 
            "ERROR: UDPBroadcast: Unable to open write socket" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return;
    }

    //Set broadcats permission
	int opt = 1;
	int error = setsockopt(_writeFd, SOL_SOCKET, 
		SO_BROADCAST, (const char *)  &opt, sizeof(opt));
    if (error == -1) {
        std::cout << 
            "ERROR: UDPBroadcast: Unable to configure write socket" << std::endl;
        std::cout << strerror(errno) << std::endl;
        closeWrite();
        return;
    }
}

void UDPBroadcast::closeRead()
{
    if (_readFd != -1) {
#ifndef MSVC
        close(_readFd);
#else
		closesocket(_readFd);
#endif
        _readFd = -1;
    }
}
void UDPBroadcast::closeWrite()
{
    if (_writeFd != -1) {
#ifndef MSVC
		close(_writeFd);
#else
		closesocket(_writeFd);
#endif
		_writeFd = -1;
    }
}
        
void UDPBroadcast::broadcastMessage(unsigned char* data, size_t len)
{
    if (_writeFd == -1) {
        std::cout << 
            "WARNING: UDPBroadcast: closed write socket" << std::endl;
        openWrite();
        return;
    }
   
    if (_broadcastAddr.size() == 0) {
        std::cout << 
            "WARNING: UDPBroadcast: no broadcast address" << std::endl;
        return;
    }

    //Send message to all broadcast address
    for (size_t i=0;i<_broadcastAddr.size();i++) {
        struct sockaddr_in addr;
#ifndef MSVC
        bzero(&addr, sizeof(addr));
#else
		ZeroMemory(&addr, sizeof(addr));
#endif
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = _broadcastAddr[i];
        addr.sin_port = htons(_port);
          
        int error = sendto(_writeFd, (const char *) data, len, 0,
            (struct sockaddr*)&addr, sizeof(addr));

        if (error == -1) {
            std::cout << 
                "ERROR: UDPBroadcast: send failed" << std::endl;
            std::cout << strerror(errno) << std::endl;
        } else if (error != (int)len) {
            std::cout << 
                "ERROR: UDPBroadcast: send truncated" << std::endl;
            std::cout << strerror(errno) << std::endl;
        }
    }
}
        
bool UDPBroadcast::checkMessage(unsigned char* data, size_t& len)
{
    if (_readFd == -1) {
        std::cout << 
            "WARNING: UDPBroadcast: closed read socket" << std::endl;
        openRead();
        return false;
    }
   

    int size = recvfrom(_readFd, (char *) data, len, MSG_DONTWAIT, NULL, NULL);
    if (size == -1) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            std::cout << 
                "ERROR: UDPBroadcast: receive failed" << std::endl;
            std::cout << strerror(errno) << std::endl;
        } 
        return false;
    } else {
        len = size;
        return true;
    }
}
        
void UDPBroadcast::retrieveBroadcastAddress()
{
    _broadcastAddr.clear();
        
#ifndef MSVC
    struct ifaddrs* ifap;
    if (getifaddrs(&ifap) == -1) {
        std::cout << 
            "ERROR: UDPBroadcast: get broadcast address failed" << std::endl;
        std::cout << strerror(errno) << std::endl;
        return;
    }

    while (ifap != NULL) {
        SOCKADDR* addr = ifap->ifa_broadaddr;
        if (
            addr != NULL &&
            addr->sa_family == AF_INET && 
            (ifap->ifa_flags & IFF_UP) &&
            (ifap->ifa_flags & IFF_BROADCAST) && 
            !(ifap->ifa_flags & IFF_LOOPBACK)
        ) {
            _broadcastAddr.push_back(((SOCKADDR_IN*)addr)->sin_addr.s_addr);
        }
        ifap = ifap->ifa_next;
    }
#else
	//todo: adapter sous win si ça a un intérêt
#endif
}

}


#endif
