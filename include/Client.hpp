#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"

class Client
{
private:
	int _fd;
	std::string _nick;
public:
	Client(/* args */);
	Client(int fd, const std::string &nc);
	~Client();
	void parse(std::string command);
};

#endif