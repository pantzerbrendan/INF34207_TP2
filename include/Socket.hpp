
#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <vector>

#include "Client.hpp"
#include "exceptions/network_exception.hpp"

namespace constants
{
    static const int            DEFAULT_PORT = 13378;
    static const std::string    DEFAULT_PROTOCOL = "TCP";
    static const int            MAX_CLIENTS = 42;
}

typedef enum { INITIAL, RUNNING, // default states
    OPEN_OK, BIND_OK, LISTEN_OK, ACCEPT_OK, CLOSE_OK, // states used during initialization : all is ok
    NOT_OPEN, NOT_BIND, NOT_LISTEN, NOT_ACCEPT, NOT_CLOSE // states used during initialization : something went wrong
} e_socket_status;

namespace networking
{

    class Socket
    {
    private:
        e_socket_status         _status; // current status of the socket
        int                     _socket_fd; // file descriptor for the socket
        int                     _port; // port on which to listen
        struct protoent         *_protocol; // protocol used for the socket
        std::string             _protocol_name; // name of the protocol
        struct sockaddr_in      _s_in;
        std::vector<Client *>   _clients; // list of all connected clients
        bool                    _running;

    public: // protected ?
        Socket();
        Socket(int = constants::DEFAULT_PORT, const std::string & = constants::DEFAULT_PROTOCOL);
        ~Socket();

    public:
        void        Open();     // can throw a network_exception
        void        Bind();     // can throw a network_exception
        void        Listen();   // can throw a network_exception
        Client      *Accept();  // can throw a network_exception
        void        Close();    // can throw a network_exception

        int         get_port() const;
        int         get_socket_fd() const;
        bool        is_open() const;

        //static Socket   *create_socket(const int = constants::DEFAULT_PORT, const std::string & = constants::DEFAULT_PROTOCOL);
    };

}

#endif /* !SOCKET_HPP_ */
