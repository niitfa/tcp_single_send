#ifndef MESSAGE_TRANSMITTER_LINUX_H
#define MESSAGE_TRANSMITTER_LINUX_H

#ifdef __linux__
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#endif

#include <string>
#include <mutex>

class MessageTransmitterLinux
{
	static const int kMessageSize = 12;

	static const int kBytePositionValue1 = 0;
	static const int kBytePositionValue2 = 4;
	static const int kBytePositionValue3 = 8;

	std::string ip;
	int port;

	int sock;
	char message[kMessageSize];

	std::mutex mtx;
public:
	MessageTransmitterLinux(
		std::string ip,
		int port
	);

	~MessageTransmitterLinux() = default;

	int Connect();
	int Send(int,int,int);

};


#endif // !MESSAGE_TRANSMITTER_LINUX_H
