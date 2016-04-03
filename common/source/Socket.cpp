
#include <string>
#include <errno.h>
#include "Socket.hpp"

// UTILISER ERRNO !!!!!!!!!!!!

Socket::Socket(int port) : _port(port)
{
	if (!(this->_protocol = getprotobyname("TCP")))
		throw new std::string("lol");
}

Socket::~Socket() {}

void		Socket::open()
{
	this->_fd = socket(AF_INET, SOCK_STREAM, this->_protocol->p_proto);
	this->_serv_addr.sin_family = AF_INET;
	this->_serv_addr.sin_addr = INADDR_ANY;
	this->_serv_port = htons(this->_port);

	if (bind(this->_fd, (const struct sockaddr *) &this->_serv_addr, sizeof(this->_serv_addr)) == -1)
	{
		if (!this->close())
			throw new std::string("lol"); // pas reussi a fermer
		throw new std::string("lol"); // bind fail
	}
	return (this->_fd != -1);
}

bool		Socket::close()
{
	return (close(this->_fd) != -1);
}

template <typename T>
void 		Socket::write(T data)
{

}

template <typename T>
T 			Socket::read(const int size = Constants::DEFAULT_READ_SIZE)
{

}