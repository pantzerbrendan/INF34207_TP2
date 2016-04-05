#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int handle_client(int client_fd, const char *client_ip)
{
  static const char *welcome = "Welcome ! Your IP address is : ";

  if (write(client_fd, welcome, strlen(welcome)) == -1 ||
      write(client_fd, client_ip, strlen(client_ip)) == -1 ||
      write(client_fd, '\n', 1) == -1)
      return (1);
  return (0);
}

int main()
{
  struct protoent   *pe; // protocol
  int               fd; // socket_fd
  struct sockaddr_in  s_in; //informations socket
  int               port; // port d'ecoute/ecriture

  struct sockaddr_in  s_in_client;
  socklen_t           s_in_size;
  int                 client_fd;
  char                *client_ip;

  if (ac != 2)
    return (1);
  s_in_size = sizeof(s_in_client);
  port = atoi(av[1]);
  pe = getprotobyname("TCP");
  if (!pe)
    return (1);
  fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (fd == -1)
    return (1);
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      if (close(fd) == -1)
        return (1);
      return (1);
    }
  if (listen(fd, 42) == -1)
  {
    if (close(fd) == -1)
      return (1);
    return (1);
  }

  client_fd = accept(fd, (struct sockaddr *)&s_in_client, &s_in_size);
  if (client_fd == -1)
  {
    if (close(fd) == -1)
      return (1);
    return (1);
  }

  client_ip = inet_ntoa(s_in_client.sin_addr);
  write(1, client_ip, strlen(client_ip));
  write(1, '\n', 1);
  handle_client(client_fd, client_ip);

  if (close(client_fd) == -1)
    return (1);
  if (close(fd) == -1)
    return (1);
  return (0);
}
