
#ifndef ENVIRONMENT_HPP_
# define ENVIRONMENT_HPP_

#include <string>
#include <ostream>
#include "typos.h"

class Environment
{
private:
    ss_map      _content;

public:
    Environment(char **);
    ~Environment();

    std::string     &operator[](const std::string &);
    ss_map          getContent() const;
};

std::ostream    &operator<<(std::ostream &, const Environment &);

#endif /* !ENVIRONMENT_HPP_ */
