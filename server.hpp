#pragma once 


#include <iostream>
#include <vector>                                          //-> for vector
#include <sys/socket.h>                                   //-> for socket()
#include <sys/types.h>                                   //-> for socket()
#include <netinet/in.h>                                 //-> for sockaddr_in
#include <fcntl.h>                                     //-> for fcntl()
#include <unistd.h>                                   //-> for close()
#include <arpa/inet.h>                               //-> for inet_ntoa()
#include <poll.h>                                   //-> for poll()
#include <csignal>                                 //-> for signal()

#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color

#include "client.hpp"
class client;

class server
{
        private :
            int port;
            int ser_fd_socket;
            static bool signal;
            std::vector<client> clients;
            std::vector<pollfd> fds;



        public :

        server();

	    void serverInit();
	    void SerSocket();
	    void AcceptNewclient();
	    void ReceiveNewData(int fd);

	    static void signalHandler(int signum);
    
	    void CloseFds();
	    void Clearclients(int fd);

};