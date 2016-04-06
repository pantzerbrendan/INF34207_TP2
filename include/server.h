
#ifndef server_h_
#define server_h_

#include "typos.h"
#include "Socket.hpp"
#include "Client.hpp"
#include "exceptions/network_exception.hpp"

static int g_socket_fd;

void 		signal_handler(int);
void 		client_handle(networking::Client *);
void		client_process(networking::Client *);

#endif /* !server_h_ */