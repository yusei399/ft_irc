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

#define TIMEOUT 3 * 60 * 1000

# define MSG_LEN 1024
#include "Client.hpp"
class Client;
class Server
{
private:
	int _port;
	std::string	_password;
	int _socket_fd;
	std::map<int, Client> _connect;
	std::vector<struct pollfd>		_pfds;
	void create_poll(int socket_fd);
	std::map<int, Client> _user;
public:
	Server();
	Server(int port, std::string &password);
	~Server();
	void create_soket();
	void connect_client(int socketfd);
	void chat_in(int fd);
	void start();
	void allow();
	std::map<int, Client>& get_user();
	int  search(const std::string &str, const std::string &target);
	void do_buildin(int fd, const Command &cmd);
};
void signal_handler(int signal);

#endif