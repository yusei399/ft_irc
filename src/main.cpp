#include "../include/Server.hpp"
#include <signal.h>
#include "../include/StringExtend.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include "../include/ChannelManager.hpp"


Server *server;

void signal_handler(int signal)
{
	server->close_all_fd();
	std::cout << " exit " << std::endl;
	exit(signal);
}


int main(int argc, char **argv){
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGPIPE, SIG_IGN);
    try
    {
        if (argc == 3)
        {
            std::string port_str = argv[1];
            for (int i = 0; i < port_str.length(); i++) {
                if (!isdigit(port_str[i])) {
                    std::cerr << "invalid port num" << std::endl;
                    return 1;
                }
            }
            int port = atoi(argv[1]);
            if (port < 1024 || port > 65565) {
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
