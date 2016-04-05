#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
    struct protoent       *pe;
    int                   fd;
    struct sockaddr_in    s_in;
    int                   port;
    char                  *ip;

    if (ac != 2)
    {
        return (1);
    }
    s_in_size = sizeof(s_in_client);
    ip = av[1];
    port = atoi(av[2]);
    pe = getprotobyname("TCP");
    if (!pe)
    {
        return (1);
    }
    fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    if (fd == -1)
    {
        return (1);
    }
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = INADDR_ANY; // a changer
    write(1, client_ip, strlen(client_ip));
    write(1, '\n', 1);

    if (close(client_fd) == -1)
    {
        return (1);
    }
    if (close(fd) == -1)
    {
        return (1);
    }
    return (0);
}
