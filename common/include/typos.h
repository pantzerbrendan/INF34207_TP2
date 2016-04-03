
#ifndef TYPOS_H_
# define TYPOS_H_

#include <sys/types.h>
#include <sys/Socket.h>
#include <netdb.h>

#include <string>
#include <list>
#include <map>

typedef std::map<std::string, std::string>  ss_map;
typedef std::list<std::string>              s_list;
typedef struct protoent						s_protoent;
typedef struct sockaddr_in					s_sockaddr_in;

namespace Constants
{
	static const int DEFAULT_READ_SIZE = 1024;
	static const int DEFAULT_WRITE_SIZE = 1024;
}

#endif /* !TYPOS_H_ */
