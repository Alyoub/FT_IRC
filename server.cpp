#include "Server.hpp"




bool Server::Signal = false;

Server::Server()
{
    this->fd_soket = -1;
}

Server::~Server(){}

void Server::SignalHandler(int signum)
{
    (void)signum;
    std::cout<<std::endl<<GRE<<"---------->        SIGNAL RECIEVED        <----------"<<GRE<<std::endl;
    Server::Signal = true;
}
void Server::closeFDS()
{
    for(size_t i = 0 ; i < clients.size(); i++)
    {
        int  xp = clients[i].getFD();
        xp -= 3; // xp add xp just to make it easy for user

        // std::cout<<RED<<"SERVER : CLIENT <"<<clients[i].getFD()<<"> Disconnected"<<WHI<<std::endl;
        std::cout<<RED<<"SERVER : CLIENT <"<<xp<<"> Disconnected"<<WHI<<std::endl;
        close(clients[i].getFD());
    }
    if(fd_soket == -1)
    {
        fd_soket -= 3;
        std::cout<<RED<<"SERVER <"<<fd_soket<<">  DISCONNECTED"<<WHI<<std::endl;
        close(fd_soket);
    }
        
}

void Server::Sersocket()
{  
    int option_value = 1;
    struct sockaddr_in add;

    struct pollfd Npoll;
    // struct pollfd newFd; // removed 
   

    add.sin_family = AF_INET;
    add.sin_port = htons(this->port);
    add.sin_addr.s_addr = INADDR_ANY;
   
    fd_soket = socket(AF_INET, SOCK_STREAM, 0);

    if(fd_soket == -1)
    throw(std::runtime_error("-----> CANT CREAT A VALID SOKET <-----"));
         
    if(setsockopt(fd_soket, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value)) == -1)// setsockopt == set socket option
        throw(std::runtime_error("-----> FAILED TO SET OPTION <SO_REUSEADDR> ON SOKET <-----"));
    if(fcntl(fd_soket, F_SETFL, O_NONBLOCK) == -1)
        throw(std::runtime_error("-----> FAILED TO SET OPTION <O_NONBLOCK> ON SOKET <-----"));
   //bind then listen to this server so u can use it onw IP or the same port as befor
   if(bind(fd_soket,(struct sockaddr *)&add, sizeof(add)) == -1)
        throw(std::runtime_error("-----> FAILED TO BIND THE SOKET <-----"));
    if(listen(fd_soket ,SOMAXCONN) == -1)
        throw(std::runtime_error("-----> FAILED TO LISTEN ON SOCKET <-----"));


    Npoll.fd = fd_soket; // chmn fd <socket> bari tminitori 
    Npoll.events = POLLIN; // POLLIN mean that ur ready to read data 
    Npoll.revents = 0;
    fds.push_back(Npoll); //ADD THE INFO FROM THE NPOLL STRUCT TO THE FDS VECTORS
}



void Server::ServerInit()
{
   

    this->port = 8080;
    Sersocket();

    std::cout<<ORNG<<"----->        SERVER      CONNECTED        <------"<<WHI<<std::endl;
    std::cout<<BLUE<<"          waitng to accept a conection        "<<WHI<<std::endl;

    while(Server::Signal == false)
    {
        if((poll(&fds[0],fds.size(),-1) == -1) && Server::Signal == false) //-> wait for an event
            throw(std::runtime_error("------> ERROR IN POLL <------"));
        for(size_t i = 0; i < fds.size(); i++)
        {
            if(fds[i].revents & POLLIN) // check for data to read
            {
                if(fds[i].fd == fd_soket)
                    AcceptNewclient();
                else
                    ReceiveNewData(fds[i].fd);
            }
        }
    }
    closeFDS();
}


void Server::AcceptNewclient()
{
   client New_client;

   struct sockaddr_in add_client;
   struct pollfd New_poll;

   socklen_t len_socket = sizeof(add_client);

    int accept_clinet = accept(fd_soket, (sockaddr *)&(add_client), &len_socket);

    if(accept_clinet  == - 1)
        std::cout<<RED<<"----------> ACCEPT FAILED <----------"<<WHI<<std::endl; // used for TCP ---> Transmission Control Protocol
    if(fcntl(accept_clinet, F_SETFL, O_NONBLOCK) == -1)
        throw(std::runtime_error("----->  FAILED TO SET OPTION <O_NONBLOCK> ON SOKET <-----"));

    New_poll.fd = accept_clinet;
    New_poll.events = POLLIN; // ready to start rading data 
    New_poll.revents = 0;

    New_client.setFD(accept_clinet);
    New_client.setIPadd(inet_ntoa(add_client.sin_addr)); // convert the ip to readable string
    
    clients.push_back(New_client); //add the client to the vector of clients
    fds.push_back(New_poll); // add the client socket to the struct pollfd
    
    accept_clinet -= 3;
    std::cout<<GRE<<"------>        CLIENT <"<<accept_clinet<<"> CONNECTED        <------"<<WHI<<std::endl;
   
}
void Server::ReceiveNewData(int fd)
{
    char buffer[1024]; // 1024 bytes 1Kb 
    memset(buffer, 0, sizeof(buffer)); // clear the buffer so i can evoid any leaks/erorrs 

    ssize_t bytes = recv(fd, buffer, sizeof(buffer), 0);//The recv method is essential for receiving data in a network socket programming

    int counter = 0;
    if(bytes <= 0)
    {
        counter =fd;
        counter -= 3;
        std::cout<<RED<<"------>        CLIENT <"<<counter<<"> DISCONNECTED        <------"<<WHI<<std::endl;
        Clearclients(fd); // fd client  i added counter here just to khow the number of clients <ID>
        close(fd);
    }
    else
    {
        std::string get_time = getCurrentTime();
        buffer[bytes] = '\0';
        Msg_resv();
        fd -=3;
        std::cout<<GRE<<" CLIENT <"<<fd<<"> :: "<<WHI<<buffer;
       

        // here to check for commands 

    }
        
}

void Server::Clearclients(int fd)
{
    for(size_t i = 0; i < fds.size(); i++) // remove client from the pollfd struct 
    {
        if(fds[i].fd == fd)
        {
            fds.erase(fds.begin() + i);
            break;
        }
    }
    for(size_t i = 0; i < fds.size();i++) // remove client from the clients vector 
    {
        if(clients[i].getFD() == fd )
        {
            clients.erase(clients.begin() + i);
            break;
        }
    }
}

std::string Server::getCurrentTime()
{
    std::time_t now = std::time(0); // Get current time as a time_t object
    std::tm *ltm = std::localtime(&now); // Convert to local time

    char buffer[80];
    // Format: HH:MM:SS
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", ltm);
    return std::string(buffer);
}

void Server::Msg_resv()
{
    std::string get_time = getCurrentTime();

    std::cout <<YEL<< " [" << get_time << "]"<<WHI;
}