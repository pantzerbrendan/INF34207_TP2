
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

    s_list::const_iterator it = this->_argvalues.begin();
    for (int idx = 0; idx < index && it != this->_argvalues.end(); idx++)
      it++;
    return (*(it));
}
