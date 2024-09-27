#include "server.hpp"




int main(int ac, char **av)
{

    if(ac > 2)
    {
        std::cout<<av[1]<<std::endl;
    }
    else
        std::cerr<<"USAGE  : ./ircserv <port> <password> "<<std::endl;
}