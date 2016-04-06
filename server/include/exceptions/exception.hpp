
#ifndef EXCEPTION_HPP
# define EXCEPTION_HPP

#include <exception>
#include <string>
#include <cerrno>

// # define exception(msg)         exception(msg, __FILE__, __FUNCTION__, __LINE__)
// # define pretty_exception(msg)  exception(msg, __FILE__, __PRETTY_FUNCTION__, __LINE__)

class exception : public std::exception
{
protected:
    std::string     _message;
    std::string     _file;
    std::string     _function;
    int             _line;
    int             _errnum; // = errno
    std::string     _detailed_error_message; // = strerror(errno)

public:
    exception(const std::string &);
    exception(const std::string &, const std::string &, const std::string &, const int); // message, file, function, line
    ~exception() throw();

    virtual const char  *what() const throw();
    virtual void        display() const;
};

std::ostream    &operator<<(std::ostream &, const exception &);

#endif /* !EXCEPTION_HPP */

/** exception.cpp
## adapter le code a ce qu'on a !

void        exception::display() const
{
    std::ostringstream	stringStream(std::ostringstream::ate);

	stringStream << RED << "<" << this->m_value << "> " << this->m_error;
	if (this->m_comment != "")
		stringStream << "(" << this->m_comment << ")";
	stringStream << RESET << std::endl;
	std::cerr << stringStream.str();
}

std::ostream    &operator<<(std::ostream &stream, const exception &ex)
{
    stream << RED << "<" << this->m_value << "> " << this->m_error;
    if (this->m_comment != "")
		stringStream << "(" << this->m_comment << ")";
	stringStream << RESET;
    return (stream);
}

**/
