#include "message_transmitter_linux.h"

MessageTransmitterLinux::MessageTransmitterLinux(std::string ip, int port) : ip{ ip }, port{ port }
{
	memset(this->message, 0, kMessageSize);
}

int MessageTransmitterLinux::Connect()
{
#ifdef __linux__
	sockaddr_in hint;
	memset(&hint, 0, sizeof(sockaddr_in));
	hint.sin_family = AF_INET;
	hint.sin_addr.s_addr = inet_addr(this->ip.c_str());
	hint.sin_port = htons(port);

	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
	{
		return 1;
	}

	while (connect(this->sock, (sockaddr*)&hint, sizeof(hint)) < 0)
		;

#endif
	return 0;
}

int MessageTransmitterLinux::Send(int val1, int val2, int val3)
{
	int send_size = 0;
#ifdef __linux__
	this->mtx.lock();
	memset(this->message, 0, this->kMessageSize);
	memcpy(this->message + this->kBytePositionValue1, &val1, sizeof(val1));
	memcpy(this->message + this->kBytePositionValue2, &val2, sizeof(val2));
	memcpy(this->message + this->kBytePositionValue3, &val3, sizeof(val3));
	send_size = send(this->sock, this->message, this->kMessageSize, MSG_NOSIGNAL);
	this->mtx.unlock();
#endif
	return send_size;
}