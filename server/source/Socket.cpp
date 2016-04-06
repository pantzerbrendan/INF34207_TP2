
#include <iostream>
#include <unistd.h>
#include "Socket.hpp"

networking::Socket::Socket() : _port(constants::DEFAULT_PORT), _status(INITIAL), _protocol_name(constants::DEFAULT_PROTOCOL), _running(false)
{}

networking::Socket::Socket(int port, const std::string &protocol)
    : _port(port), _status(INITIAL), _protocol_name(protocol), _running(false)
{
}

networking::Socket::~Socket()
{
    try {
        this->Close();
    } catch (network_exception ex) {
        std::cerr << ex << std::endl;
    }
}

void    networking::Socket::Open()
{
    this->_protocol = getprotobyname(this->_protocol_name.c_str());
    if (!this->_protocol)
    {
        this->_status = NOT_OPEN;
        throw network_exception("Impossible de recupérer le protocole `" + this->_protocol_name + "`");
    }

    this->_socket_fd = socket(AF_INET, SOCK_STREAM, this->_protocol->p_proto);
    if (this->_socket_fd == -1)
    {
        this->_status = NOT_OPEN;
        throw network_exception("Impossible de créer une socket");
    }

    this->_s_in.sin_family = AF_INET;
    this->_s_in.sin_port = htons(this->_port);
    this->_s_in.sin_addr.s_addr = INADDR_ANY;
    this->_status = OPEN_OK;
    this->_running = true;
}

void    networking::Socket::Bind()
{
    if (bind(this->_socket_fd, (const struct sockaddr *)&(this->_s_in), sizeof(this->_s_in)) == -1)
    {
        network_exception *except = NULL;
        try {
            this->Close();
        } catch (network_exception ex) {
            except = &ex;
        }
        this->_status = NOT_BIND;
        if (except == NULL) throw network_exception("Impossible de bind la socket");
        else throw except;
    }
    this->_status = BIND_OK;
}

void    networking::Socket::Listen()
{
    if (listen(this->_socket_fd, constants::MAX_CLIENTS) == -1)
    {
        network_exception *except = NULL;
        try {
            this->Close();
        } catch (network_exception ex) {
            except = &ex;
        }
        this->_status = NOT_LISTEN;
        if (except == NULL) throw network_exception("Impossible de listen sur la socket");
        else throw except;
    }
    this->_status = LISTEN_OK;
}

networking::Client  *networking::Socket::Accept()
{
    struct sockaddr_in s_client;
    socklen_t   s_client_size = sizeof(s_client);
    int client_fd = accept(this->_socket_fd, (struct sockaddr *)&s_client, &s_client_size);
    if (client_fd == -1)
    {
        this->_status = NOT_ACCEPT;
        throw network_exception("Erreur lors de la connexion du client");
    }
    networking::Client *cl = new networking::Client(inet_ntoa(s_client.sin_addr), client_fd, s_client);
    this->_clients.push_back(cl);
    //this->_clients.push_back(new networking::client(inet_ntoa(s_client.sin_addr), client_fd, s_client));
    this->_status = ACCEPT_OK;
    return (cl);
}

void    networking::Socket::Close()
{
    for (uint i = 0; i < this->_clients.size(); i++)
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
    this->_running = false;
}

int     networking::Socket::get_socket_fd() const { return (this->_socket_fd); }
int     networking::Socket::get_port() const { return (this->_port); }
bool    networking::Socket::is_open() const { return (this->_running); } // a changer
