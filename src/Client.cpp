#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}

void Client::command_parser(std::string &command)
{
	size_t i = 0;
	size_t j = 1;
	if (command[i] == ':')
	{
		while (command[i] != ' ')
		{
			command_parser.append(command[i], i);
			i++;
		}
		while (command[i++] == ' ')
	}
	while (command[j] == ' ' && command[i] != '\r' command[i] != '\n')
	{
		command_.append(command[j], j);
		j++;
	}
	while (command[j] == ' ')
		j++;
}