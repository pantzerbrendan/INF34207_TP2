
#ifndef NETWORK_EXCEPTION_HPP_
# define NETWORK_EXCEPTION_HPP_

#include <exception>
#include <string>
#include "exception.hpp"

# define network_exception(msg)         network_exception(msg,__FILE__, __FUNCTION__, __LINE__)
# define pretty_network_exception(msg)  network_exception(msg,__FILE__, __PRETTY_FUNCTION__, __LINE__)

class network_exception : public exception
{
public:
    network_exception(const std::string &, const std::string &, const std::string &, const int);
    ~network_exception() throw();

    virtual const char  *what() const throw();
};

#endif /* !NETWORK_EXCEPTION_HPP_ */
