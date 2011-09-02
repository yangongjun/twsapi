#ifndef eposixclientsocketcommon_def
#define eposixclientsocketcommon_def

#include "config.h"

#ifdef _WIN32
	// Windows
	// includes
	#ifdef NEED_WINVER_XP
		#define WINVER 0x0501
	#endif
	# ifdef HAVE_WS2TCPIP_H
		#include <ws2tcpip.h>
	# endif
	# ifdef HAVE_WSPIAPI_H
		#include <wspiapi.h>
	# endif

	#include <winsock2.h>
	#include <time.h>

	// defines
	#define EISCONN WSAEISCONN
	#define EWOULDBLOCK WSAEWOULDBLOCK
	#define ECONNREFUSED WSAECONNREFUSED

	namespace IB {
	// helpers
	inline bool SocketsInit( void) {
		WSADATA data;
		return ( !WSAStartup( MAKEWORD(2, 2), &data));
	};
	inline bool SocketsDestroy() { return ( !WSACleanup()); };
	inline int SocketClose(int sockfd) { return closesocket( sockfd); };
	}

#else
	// LINUX
	// includes
	#include <arpa/inet.h>
	#include <errno.h>
	#include <sys/select.h>
	#include <netdb.h>

	namespace IB {
	// helpers
	inline bool SocketsInit() { return true; };
	inline bool SocketsDestroy() { return true; };
	inline int SocketClose(int sockfd) { return close( sockfd); };
	}

#endif

#endif
