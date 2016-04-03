
#ifndef TYPOS_H_
# define TYPOS_H_

#include <string>
#include <list>
#include <map>

typedef std::map<std::string, std::string>  ss_map;
typedef std::list<std::string>              s_list;

namespace Constants
{
	static const int DEFAULT_READ_SIZE = 1024;
	static const int DEFAULT_WRITE_SIZE = 1024;
}

#endif /* !TYPOS_H_ */
