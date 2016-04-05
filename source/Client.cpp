
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