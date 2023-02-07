#include "../include/Server.hpp"


void signal_handler(int signal)
{
	
}

Server *server;
int main(int argc, char **argv){

	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
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
