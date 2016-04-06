
// cette classe n'est pas la classe pour le client (application), mais
// pour representer un client qui se connecte au serveur

#ifndef client_hpp_
# define client_hpp_

#include <netdb.h>
#include <string>
#include "typos.h"

namespace networking
{

    class Client
    {
    private:
        int                 _fd;
        std::string         _ip_addr;
        struct sockaddr_in  _s_in;
        socklen_t           _s_in_size;
        pid_t               _pid;

    public:
        Client(const char *, const int, struct sockaddr_in); // ip, fd, s_in
        Client(const std::string &, const int, struct sockaddr_in);
        ~Client();

        void                CloseConnection();

        const std::string   &get_ip_address() const;
        int                 get_fd() const;
        bool                is_open();
        void                set_pid(pid_t);
    };

}

#endif /* !client_hpp_ */
