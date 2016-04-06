
#include "exceptions/network_exception.hpp"

network_exception::network_exception(const std::string &mess) : exception(mess) {}
network_exception::network_exception(const std::string &mess, const std::string &file, const std::string &function, const int line) :exception(mess, file, function, line) {}
network_exception::~network_exception() throw() {}
