
#include <iostream>
#include <fstream>
#include <signal.h>
#include <unistd.h>
#include <strings.h>

#include "server.h"

void 		signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (close(g_socket_fd) == -1)
			std::cerr << "Impossible de fermer la socket" << std::endl;
		std::cout << "L'application va se fermer" << std::endl;
		exit(0);
	}
}

void 		client_handle(networking::Client *c)
{
	pid_t	pid = fork();
	if (pid == -1)
	{
		std::cerr << "Impossible de forker pour le client @" << c->get_ip_address() << std::endl;
	}
	else if (pid == 0)
	{
		c->set_pid(pid);
		client_process(c);
	}
}

void		client_process(networking::Client *c)
{
	try {
		// child process
		bool running = true;
		bool in_file = false;
		std::string filename = "";
		while (running)
		{
			running = false;
			char buffer[constants::READ_SIZE];
			bzero(buffer, constants::READ_SIZE);
			int rd = read(c->get_fd(), buffer, constants::READ_SIZE);
			if (rd == -1)
			{
				std::cerr << "Erreur lors de la lecture" << std::endl;
				c->CloseConnection();
			}
			else if (rd == 0)
			{
				running = false;
				std::clog << "Le client `" << c->get_ip_address() << "` s'est deconnecte..." << std::endl;
			}

			else
			{
				running = true;
				std::string read_str = std::string((char *)buffer);
				if (in_file)
				{
					if (rd == constants::READ_SIZE)
						read_str = read_str.substr(0, read_str.size() - 3);
					std::ofstream outfile;
					outfile.open(filename, std::ofstream::out | std::ofstream::app);
					outfile << read_str;
					outfile.close();
					if (rd < constants::READ_SIZE)
					{
						in_file = false;
						filename = "";
					}
				}
				else
				{
						read_str = read_str.substr(0, read_str.size()); // supprime le \n a la fin de la chaine
						if (read_str.find("FILE_NAME = ") == 0)
						{
							filename = constants::FILES_PATH + read_str.substr(12);
							std::ofstream outfile(filename.c_str());
							std::clog << "Un nouveau fichier (" << filename << ") a ete cree." << std::endl;
							in_file = true;
						}
					}
				}
			}
		} catch (network_exception ex) {
			std::cerr << ex.what() << std::endl;
		}
	}
