
#include <iostream>
#include <string>
#include <cstdlib>
#include "INF34207_client.hpp" // ../include
#include "Parameters.hpp" // ../../common/include

static void help()
{
    std::cout << "AIDE" << std::endl;
}

int main(int ac, char **av, char **env)
{
    Parameters params(ac, av, env);

    if (params.count() == 2)
    {
        if (params.values(1) == "--help")
            help();
        else
            help(); // erreur
    }
    else if (params.count() == 3)
        help();//client(params);
    else
        help(); // erreur

    return (EXIT_SUCCESS);
}
