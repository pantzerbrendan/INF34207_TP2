
#include <sstream>
#include <cerrno>
#include <cstring>
#include "exceptions/exception.hpp"

exception::exception(const std::string &mess)
{
	this->_message = mess;
	this->_errnum = errno;
	this->_detailed_error_message = strerror(errno);
}

exception::exception(const std::string &mess, const std::string &file, const std::string &function, const int line)
{
	this->_message = mess;
	this->_file = file;
	this->_function = function;
	this->_line = line;
	this->_errnum = errno;
	this->_detailed_error_message = strerror(errno);
}

exception::~exception() throw() {}

const char	*exception::what() const throw()
{
	return this->_message.c_str();
}

void		exception::display() const
{
	// std::ostringstream	stringStream(std::ostringstream::ate);

	// stringStream << RED << "<" << this->m_value << "> " << this->m_error;
	// if (this->m_comment != "")
	// 	stringStream << "(" << this->m_comment << ")";
	// stringStream << RESET << std::endl;
	// std::cerr << stringStream.str();
}

std::ostream 	&operator<<(std::ostream &stream, const exception &ex)
{
	stream << ex.what();
	return (stream);
}