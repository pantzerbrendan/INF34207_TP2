
#include "Environment.hpp" // ../include

Environment::Environment(char **env)
{
    for (int i = 0; env[i]; i++)
    {
        std::string current = std::string(env[i]);
        int index = current.find("=");
        if (index != -1)
        {
            std::string key = current.substr(0, index++);
            std::string value = current.substr(index);

            this->_content[key] = value;
        }
    }
}

Environment::~Environment() { this->_content.clear(); }

ss_map          Environment::getContent() const { return this->_content; }
std::string     &Environment::operator[](const std::string &key) { return this->_content[key]; }

std::ostream    &operator<<(std::ostream &stream, const Environment &env)
{
    ss_map::const_iterator it;
    ss_map content = env.getContent();
    for (it = content.begin(); it != content.end(); it++)
        stream << it->first << "=" << it->second << std::endl;
    return (stream);
}
