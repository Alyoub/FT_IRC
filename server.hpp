#pragma once 



#include <iostream>
#include <vector>                                        
#include <sys/socket.h>                                 
#include <sys/types.h>                                
#include <netinet/in.h>                             
#include <fcntl.h>                                
#include <unistd.h>                                 
#include <arpa/inet.h>                            
#include <poll.h>                               
#include <csignal>                                

#define RED "\e[1;31m"
#define WHI "\e[0;37m" 
#define GRE "\e[1;32m"
#define YEL "\e[1;33m" 
#define ORNG "\033[33m"
#define BLUE "\033[34m"

#include "client.hpp"

class Server
{
    private:
    static bool Signal;
    int fd_soket;
    std::vector<client> clients;
    std::vector<pollfd>fds;
    int port;




    public :

    Server();
    ~Server();
    static void SignalHandler(int signum);
    void ServerInit();
    void Sersocket();
    void closeFDS();
    void AcceptNewclient();
    void ReceiveNewData(int fd);
    void Clearclients(int fd);


    // for time 

    std::string getCurrentTime();
    void Msg_resv();
};