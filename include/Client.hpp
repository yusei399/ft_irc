#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"

class Client
{
private:
	int _fd;
	std::string _nick;
	std::string _command_parse;
	std::string _command;
	std::vector<std::string> _params;

public:
	Client(/* args */);
	Client(int fd, const std::string &nc);
	~Client();
	void command_parser(std::string &command);
	void preprocessing(const std::string &message, int &i);
	void processingparams(const std::string &message, int &i);

};

#endif