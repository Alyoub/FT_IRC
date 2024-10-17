#include "server.hpp"
#include "client.hpp"




int main()
{
	server ser;
	std::cout << "---- SERVER ----" << std::endl;
	try{
		signal(SIGINT, server::SignalHandler);
		signal(SIGQUIT, server::SignalHandler);
		ser.ServerInit();
	}
	catch(const std::exception& e){
		ser.CloseFds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}