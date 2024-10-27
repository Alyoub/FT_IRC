#include "Server.hpp"
#include "client.hpp"




int main()
{
	Server ser;
	std::cout<<YEL<<"-------------> 			SERVER			<-------------"<<WHI<<std::endl;
	try{
		signal(SIGINT, Server::SignalHandler); //-> catch the signal (ctrl + c)
		signal(SIGQUIT, Server::SignalHandler); //-> catch the signal (ctrl + \)
		ser.ServerInit(); //-> initialize the server
	}
	catch(const std::exception& e){
		ser.closeFDS(); //-> close the file descriptors
		std::cerr << e.what() << std::endl;
	}
	 std::cout<<BLUE<<"------------->        Server  Closed        <------------- "<<BLUE<<std::endl;
}

//run as client   localhost : 127.0.0.1  port : 4444 