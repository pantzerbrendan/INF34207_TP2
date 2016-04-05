
#include <iostream>
#include "socket.hpp"

networking::socket::socket(const int port = constants::DEFAULT_PORT, const std::string &protocol = constants::DEFAULT_PROTOCOL)
    : _port(port), _status(INITIAL), _protocol_name(protocol)
{
}

networking::socket::~socket()
{
    try {
        this->close();
    } catch (network_exception ex) {
        std::cerr << ex << std::endl;
    }
}

void    networking::socket::open()
{
    this->_protocol = getprotobyname(this->_protocol_name);
    if (!this->_protocol)
    {
        this->_status = NOT_OPEN;
        throw network_exception("Impossible de recupérer le protocole `" + this->_protocol_name + "`");
    }

    this->_socket_fd = socket(AF_INET, SOCK_STREAM, this->_protocol->p_proto);
    if (this->_socket_fd = -1)
    {
        this->_status = NOT_OPEN;
        throw network_exception("Impossible de créer une socket");
    }

    this->_s_in.sin_family = AF_INET;
    this->_s_in.sin_port = htons(this->_port);
    this->_s_in.sin_addr.s_addr = INADDR_ANY;
    this->_status = OPEN_OK;
}

void    networking::socket::bind()
{
    if (bind(this->_socket_fd, (const struct sockaddr *)&(this->_s_in), sizeof(this->_s_in)) == -1)
    {
        network_exception *except = NULL;
        try {
            this->close();
        } catch (network_exception ex) {
            except = &ex;
        }
        this->_status = NOT_BIND;
        throw except == NULL ? network_exception("Impossible de binder la socket") : except; // man bind
    }
    this->_status = BIND_OK;
}

void    networking::socket::listen()
{
    if (listen(this->_socket_fd, MAX_CLIENTS) == -1)
    {
        network_exception *except = NULL;
        try {
            this->close();
        } catch (network_exception ex) {
            except = &ex;
        }
        this->_status = NOT_LISTEN;
        throw except == NULL ? network_exception("Impossible de listen sur la socket") : except; // man bind
    }
    this->_status = LISTEN_OK;
}

networking::client  *networking::socket::accept()
{
    struct sockaddr_in s_client;
    socklen_t   s_client_size = sizeof(s_client);
    int client_fd = accept(this->_socket_fd, (struct sockaddr *)&s_client, &s_client_size);
    if (client_fd == -1)
    {
        this->_status = NOT_ACCEPT;
        throw network_exception("Erreur lors de la connexion du client");
    }
    this->_clients.push_back(new networking::client(inet_ntoa(s_client.sin_addr, fd, s_client)));
    this->_status = ACCEPT_OK;
    return (client);
}

void    networking::socket::close()
{
    for (int i = 0; i < this->_clients.size(); i++)
    {
        if (close(this->_socket_fd) == -1)
            std::cerr << "Erreur lors de la deconnexion du client : " << this->_clients[i]->get_ip_address() << std::endl;
        else
            delete this->_clients[i];
    }
    this->_clients.clear();
    if (close(this->_socket_fd) == -1)
    {
        this->_status = NOT_CLOSE;
        throw network_exception("Erreur lors de la fermeture de la socket");
    }
}

static socket *networking::socket::create_socket(const int port, const std::string &protocol_name)
{
    socket sock = new socket(port, protocol_name);
    try {
        sock->open();
        sock->bind();
        sock->listen();
    } catch (network_exception ex) {
        return (NULL);
    }
    return (sock);
}
