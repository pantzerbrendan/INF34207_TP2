
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

    std::cout << params.values(1) << std::endl;
    if (params.count() == 2 && params.values(1) == "--help")
        help();
    // if (ac == 2 && std::string(av[1]) == "--help")
    //     help_fct();

    return (EXIT_SUCCESS);
}
