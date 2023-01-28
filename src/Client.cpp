#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}

void Client::command_parser(std::string &command)
{
	int  i = 0;
	size_t j = 1;
	if (command[i] == ':')
		this->preprocessing(command, i);
	while (command[j] == ' ' && command[i] != '\r' && command[i] != '\n')
	{
		_command.append(command[j], j);
		j++;
	}
	while (command[j] == ' ')
		j++;
}

void Client::preprocessing(const std::string &message, int &i)
{
	int cnt = 0;
	for (i = 1; i < message.size(); i++)
	{
		if (message[i] == ' ')
		{
			cnt = i;
			break ;
		}
		_command_parse.append(message[i], 1);
	}
	while (message[cnt] == ' ')
		cnt++;
}