#include "../include/Server.hpp"

Server *server;
int main(int argc, char **argv){
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
		std::cout << "Error ARGUMENT" << std::endl;
		return 1;
	}
}