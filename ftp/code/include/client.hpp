
// cette classe n'est pas la classe pour le client (application), mais
// pour representer un client qui se connecte au serveur

#ifndef client_hpp_
# define client_hpp_

// include pour sockaddr_in & socklen_t
#include <string>

namespace networking
{

    class client
    {
    private:
        int                 _fd;
        std::string         _ip_addr;
        struct sockaddr_in  s_in;
        socklen_t           s_in_size;

    public:
        client(const char *, const int, struct sockaddr_in); // ip, fd, s_in
        client(const std::string &, const int, struct sockaddr_in);

        const std::string   &get_ip_address() const;
    };

}

#endif /* !client_hpp_ */
