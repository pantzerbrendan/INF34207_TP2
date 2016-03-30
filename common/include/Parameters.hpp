
#ifndef PARAMETERS_HPP_
#define PARAMETERS_HPP_

#include <list>
#include <string>

#include "typos.h"
#include "Environment.hpp" // ./

class Parameters
{
private:
    int             _argcount;
    s_list          _argvalues;
    Environment     *_env;

public:
    Parameters(int, char **, char **);
    ~Parameters();

    Environment     *getEnvironment() const;
    const std::string   values(const int) const;
    int                 count() const;
};

#endif /* !PARAMETERS_HPP_ */
