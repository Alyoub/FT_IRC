#include "server.hpp"
#include "client.hpp"




int main()
{
	server ser;
	std::cout << "---- server ----" << std::endl;
	try{
		signal(SIGINT, server::signalHandler); //-> catch the signal (ctrl + c)
		signal(SIGQUIT, server::signalHandler); //-> catch the signal (ctrl + \)
		ser.serverInit(); //-> initialize the server
	}
	catch(const std::exception& e){
		ser.CloseFds(); //-> close the file descriptors
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The server Closed!" << std::endl;
}





//as args u can use  nc as the first arg and the local host as 127.0.0.1 then the port as 4444 . to add a new client