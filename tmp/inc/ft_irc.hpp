#ifndef  FT_IRC_HPP
# define FT_IRC_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>

class Ircserv
{
public:
	Ircserv();
	Ircserv(const Ircserv &);
	Ircserv &operator=(const Ircserv &);
	~Ircserv();
	int initSearv(int port, const std::string &password);

private:
	int _port;
	int _socket;
	std::string _password;
	
};

#endif // ! FT_IRC_HPP
