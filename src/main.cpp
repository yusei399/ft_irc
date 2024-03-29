#include "../include/Server.hpp"
#include <signal.h>
#include "../include/StringExtend.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include "../include/ChannelManager.hpp"
#include "FtCfunc.hpp"

Server *server;

void signal_handler(int signal)
{
	server->close_all_fd();
	std::cout << " exit " << std::endl;
	std::exit(signal);
}


int main(int argc, char **argv){
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGPIPE, SIG_IGN);
    try
    {
        if (argc == 3)
        {
            int port = ft_atoi(argv[1], 1024, 65535, dont_allow_operator);
            if (port == -1) {
                std::cerr << "invalid port num" << std::endl;
                return 1;
            }
            std::string password(argv[2]);
            Server serv(port, password);
            server = &serv;
            serv.start();
        }
        else
            std::cerr << "arg error" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
// PASS 1234
// NICK b
// USER a b c :d
// NAMES
//INVITE c #aa
// MODE #a i
