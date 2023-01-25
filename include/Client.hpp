#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"

class Client
{
private:
	int _fd;
	std::string _nick;
	std::string command_parser;
	std::string command_;
public:
	Client(/* args */);
	Client(int fd, const std::string &nc);
	~Client();
	void command_parser(std::string command);
};

#endif