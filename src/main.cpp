#include "../include/Server.hpp"
#include <signal.h>


void signal_handler(int signal)
{
	std::cout << " exit " << std::endl;
	exit(signal);
}

Server *server;
int main(int argc, char **argv){
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		if (argc == 3)
		{
			int port = atoi(argv[1]);
			std::string password(argv[2]);
			Server Irc(port, password);
			server = &Irc;
			Irc.start();
		}
		else
			std::cerr << "arg error" << std::endl;
	}
	catch(const std::exception& e)
		std::cerr << e.what() << '\n';
}
