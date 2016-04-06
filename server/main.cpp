
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <strings.h>

#include "server.h"
#include "Socket.hpp"
#include "Client.hpp"
#include "exceptions/network_exception.hpp"

int main(int ac, char **av)
{
	networking::Socket s(23456, "TCP");

	signal(SIGINT, &signal_handler);
	try {
		s.Open();
		s.Bind();
		s.Listen();
	} catch (network_exception ex) {
		std::cerr << ex.what() << std::endl;
	}

	g_socket_fd = s.get_socket_fd();
	std::cout << "Le port est : " << s.get_port() << std::endl;
	while (s.is_open())
	{
		try
		{
			networking::Client *c = s.Accept();
			std::cout << c->get_ip_address() << " connected" << std::endl;
			client_handle(c);
		} catch(network_exception ex) {
			std::cerr << ex.what() << std::endl;
		}
	}

	try {
		s.Close();
	} catch (network_exception ex) {
		std::cerr << ex.what() << std::endl;
	}

	(void)ac;
	(void)av;
	return (0);
}
