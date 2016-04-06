
#ifndef TYPOS_H_
#define TYPOS_H_

namespace constants
{
    static const int            DEFAULT_PORT = 13378;
    static const std::string    DEFAULT_PROTOCOL = "TCP";
    static const int            MAX_CLIENTS = 42;
    static const int            READ_SIZE = 2048;
    static const std::string    FILES_PATH = "./data/";
}

typedef enum { INITIAL, RUNNING, // default states
    OPEN_OK, BIND_OK, LISTEN_OK, ACCEPT_OK, CLOSE_OK, // states used during initialization : all is ok
    NOT_OPEN, NOT_BIND, NOT_LISTEN, NOT_ACCEPT, NOT_CLOSE // states used during initialization : something went wrong
} e_socket_status;

#endif /* !TYPOS_H_ */