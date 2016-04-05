
#include <iostream>
#include <signal.h>
#include <unistd.h>

#include "Socket.hpp"
#include "Client.hpp"
#include "exceptions/network_exception.hpp"

static int g_socket_fd;

void 		signal_handler(int signum)
{
	if (signum == SIGKILL)
	{
		if (close(g_socket_fd) == -1)
			std::cerr << "Impossible de fermer la socket" << std::endl;
	}
}

int main(int ac, char **av)
{
	networking::Socket s(23456, "TCP");

	signal(SIGKILL, &signal_handler);
	try {
		s.Open();
		s.Bind();
		s.Listen();
	} catch (network_exception ex) {
		std::cerr << ex.what() << std::endl;
	}

	g_socket_fd = s.get_socket_fd();
	while (s.is_open())
	{
		try
		{
			networking::Client *c = s.Accept();
			std::cout << c->get_ip_address() << " connected" << std::endl;
		} catch(network_exception ex) {
//			std::cerr << ex.what() << std::endl
		}
	}

	try {
		s.Close();
	} catch (network_exception ex) {
		std::cerr << ex.what() << std::endl;
	}

	return (0);
}