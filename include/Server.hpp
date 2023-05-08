#ifndef SERVER_HPP
#define SERVER_HPP 

#include <iostream>
#include <algorithm>
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string> 
#include <fcntl.h>
#include <signal.h>
#include <sys/poll.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Command.hpp"
#include "Message.hpp"
#include "ChannelManager.hpp"
#include "ClientManager.hpp"
#define TIMEOUT 3 * 60 * 1000

# define MSG_LEN 1024

class Client;
class Server
{
private:
	ChannelManager channelManager;
	ClientManager clientManager;
	int _port;
	std::string	_password;
	int _socket_fd;
	std::vector<struct pollfd>		_pfds;
	void create_poll(int socket_fd);
	public:
	Server();
	Server(int port, std::string &password);
	~Server();
	void create_soket();
	void connect_client(int socketfd);
	void chat_in(int fd);
	void start();
	void allow();
	void build_in(int fd, const Command &cmd);
};
void signal_handler(int signal);

#endif