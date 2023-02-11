#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}

void Client::command_parser(std::string &command)
{
	int  i = 0;
	int  cnt = 1;
	if (command[i] == ':')
		this->preprocessing(command, i);
	for (int i = 0; i < command.size(); i++)
	{
		cnt = i;
		if (command[i] == ' ' && command[i] != '\r' && command[i] != '\n')
			break;
		_command.append(command[i], i);
	}
	for (; command[cnt] == ' '; cnt++){}
	this->processingparams(&command[cnt], cnt);
}

void Client::preprocessing(const std::string &message, int &i)
{
	int cnt = 0;
	for (i = 1; i < message.size(); i++)
	{
		cnt = i;
		if (message[i] == ' ')
			break ;
		_command_parse.append(message[i], 1);
	}
	for (; message[cnt] == ' '; cnt++){}
}

void Client::processingparams(const std::string &message, int &cnt)
{
	for (; cnt < message.size(); cnt++)
	{
		std::string tmp;
		if (message[cnt] == ' ' && message[cnt] != '\r' && message[cnt] != '\n')
			break ;
		if (message[cnt] == ':')
		{
			cnt++;
			for (; cnt < message.size(); cnt++)
			{
				if (message[cnt] != '\r' && message[cnt] != '\n')
					tmp.append(message[cnt], 1);
			}
		}
		for (; cnt < message.size(); cnt++)
		{
			if (message[cnt] == ' ' &&  message[cnt] != '\r' && message[cnt] != '\n')
				tmp.append(message[cnt], 1);
		}
		_params.push_back(tmp);
	}
}


int Client::get_client_fd()
{
	return (_fd);
}