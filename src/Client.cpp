#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}

void Client::command_parser(std::string command)
{
	for (int i = 0; i < command.size(); i++)
	{
		
	}
}