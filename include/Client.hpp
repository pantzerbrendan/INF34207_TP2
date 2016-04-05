
// cette classe n'est pas la classe pour le client (application), mais
// pour representer un client qui se connecte au serveur

#ifndef client_hpp_
# define client_hpp_

// include pour sockaddr_in & socklen_t
#include <netdb.h>
#include <string>

namespace networking
{

    class Client
    {
    private:
        int                 _fd;
        std::string         _ip_addr;
        struct sockaddr_in  _s_in;
        socklen_t           _s_in_size;

    public:
        Client(const char *, const int, struct sockaddr_in); // ip, fd, s_in
        Client(const std::string &, const int, struct sockaddr_in);
        ~Client();

        const std::string   &get_ip_address() const;
    };

}

#endif /* !client_hpp_ */
