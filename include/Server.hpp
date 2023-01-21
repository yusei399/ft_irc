#ifndef SERVER_HPP
#define SERVER_HPP 

#include <iostream> 
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

#define TIMEOUT 3 * 60 * 1000


#include "Client.hpp"
class Client;
class Server
{
private:
	int _port;
	std::string	_password;
	int _socket_fd;
	std::map<int, Client> _connect;
	std::vector<struct pollfd>		_pfds;;
	void create_poll(int socket_fd);

public:
	Server();
	Server(int port, std::string &password);
	~Server();
	void create_soket();
	void connect_client(int socketfd);
	void chat_in();
	void start();
	void allow();
};

// void signal_handler(int signal);

#endif