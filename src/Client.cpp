#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}

/*
void Client::command_parser(std::string &command)
{
	int  i = 0;
	int  cnt = 1;
	//if (command[i] == ':')
	//	this->preprocessing(command, i);
	for (int i = 0; i < command.size(); i++)
	{
		cnt = i;
		//if (command[i] == ' ' && command[i] != '\r' && command[i] != '\n')
		//	break;
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
*/

int Client::get_fd() const
{
	return (_fd);
}

std::string Client::get_nick() const
{
	return (_nick);
}

std::string Client::get_real_name() const
{
	return _real_name;
}

std::string Client::get_host_name() const
{
	return _hostname;
}


/*void	send_message(const std::string &message, int fd, int flag)
{
	send(fd, message.c_str(), message.size(), flag);
}


void	Client::send_err_msg(int err_code) const
{
	send_message(std::to_string(err_code)+" "+get_nick()+ " " + get_err_msg(err_code), get_fd(), 0);
}*/


/*void	Client::send_err_msg(int err_code, const std::string &message) const
{
	send_message(std::to_string(err_code)+" "+get_nick()+ " " + message, get_fd(), 0);
}*/

//Setのキーに使うために必要
bool Client::operator<(const Client& rhs) const
{
	return get_fd() < rhs.get_fd();
}

//n
bool Client::operator==(const Client& rhs) const
{
	return get_fd() == rhs.get_fd() && get_real_name() == rhs.get_real_name();
}

//n
bool Client::operator!=(const Client& rhs) const
{
	return !operator==(rhs);
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
	os<<"nick_name : " <<client.get_nick()<<std::endl;
	os<<"real_name : " <<client.get_real_name()<<std::endl;
	os<<"host_name : " <<client.get_host_name()<<std::endl;
	os<<"fd : " << client.get_fd()<<std::endl;
}
