#ifndef SOCKET_HPP_
#define SOCKET_HPP_

#include <sys/types.h>
#include <sys/Socket.h>
#include <netdb.h>

#include "typos.h"

class Socket
{
private:
	int				_fd;
	s_protoent		_protocol;
	int 			_port;
	s_sockaddr_in	_serv_addr;

public:
	Socket(int);
	~Socket();

	template <typename T>
	void		write(T data);

	template <typename T>
	T 			read(const int = Constants::DEFAULT_READ_SIZE);

	void 		open();
	bool		close();
};

#endif /* !SOCKET_HPP_ */