#include "../include/Server.hpp"
#include <signal.h>


void signal_handler(int signal)
{
	std::cout << "test" << std::endl;
}

Server *server;
int main(int argc, char **argv){
	signal(SIGINT, signal_handler);
	
	if (argc == 3)
	{
		int port = atoi(argv[1]);
		std::string password(argv[2]);
		Server Irc(port, password);
		server = &Irc;
		Irc.start();
	}
	else
	{
		std::cout << "Error " << std::endl;
		return 1;
	}
}
