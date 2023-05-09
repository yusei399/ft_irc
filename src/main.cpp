#include "../include/Server.hpp"
#include <signal.h>
#include "../include/StringExtend.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include "../include/ChannelManager.hpp"


void signal_handler(int signal)
{
	std::cout << " exit " << std::endl;
	exit(signal);
}

//Server *server;

int main(int argc, char **argv){
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGPIPE, SIG_IGN);
	try
	{
		if (argc == 3)
		{
			//todo portが数字でない時
			int port = atoi(argv[1]);
			std::string password(argv[2]);
			Server(port, password).start();
		}
		else
			std::cerr << "arg error" << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
// PASS 1234
// NICK bcmp
// USER a b c :d
// NAMES
//INVITE bcmp #aa