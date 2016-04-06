
#include <unistd.h>
#include "exceptions/network_exception.hpp"
#include "Client.hpp"

networking::Client::Client(const char *ip_addr, const int fd, struct sockaddr_in s_in)
{
	this->_ip_addr = std::string(ip_addr);
	this->_fd = fd;
	this->_s_in = s_in;
	this->_s_in_size = sizeof(this->_s_in);
}

networking::Client::Client(const std::string &ip_addr, const int fd,struct sockaddr_in s_in)
{
	this->_ip_addr = ip_addr;
	this->_fd = fd;
	this->_s_in = s_in;
	this->_s_in_size = sizeof(this->_s_in);
}

networking::Client::~Client() {}

const std::string	&networking::Client::get_ip_address() const
{
	return (this->_ip_addr);
}

bool			networking::Client::is_open()
{
	int error;
	socklen_t len = sizeof(error);
	int retval = getsockopt(this->_fd, SOL_SOCKET, SO_ERROR, &error, &len);

	if (retval != 0 || error != 0)
		return (false);
	return (true);
}

void			networking::Client::CloseConnection()
{
	if (close(this->_fd) == -1) {
		throw network_exception("Erreur lors de la fermeture de la connexion");
	}
}

int	 			networking::Client::get_fd() const { return (this->_fd); }

void 			networking::Client::set_pid(pid_t pid) { this->_pid = pid; }