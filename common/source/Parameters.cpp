
#include "Parameters.hpp" // ../include

Parameters::Parameters(int ac, char **av, char **env)
{
    this->_argcount = ac;
    for (int i = 0; av[i]; i++) // while av[i] != NULL => i++
        this->_argvalues.push_back(std::string(av[i]));
    this->_env = new Environment(env);
}

Parameters::~Parameters()
{
    this->_argvalues.clear();
    delete this->_env;
}

Environment     *Parameters::getEnvironment() const { return (this->_env); }

int                 Parameters::count() const { return this->_argcount; }

const std::string   Parameters::values(const int index) const
{
    if (index >= this->_argcount) return (std::string());

    s_list::const_iterator it;
    for (it = this->_argvalues.begin(); it != this->_argvalues.end(); it++);
    return (*(it));
}
