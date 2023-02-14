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
	bool _permission;

public:
	Client(/* args */);
	Client(int fd, const std::string &nc);
	~Client();
	void command_parser(std::string &command);
	void preprocessing(const std::string &message, int &i);
	void processingparams(const std::string &message, int &i);
	int get_client_fd();
	std::string get_nick();
	const std::vector<std::string> &get_params() const {return _params;}
	void set_permission(bool permission) {_permission = permission;}
};

void send_message(const std::string &message, int fd, int flag);
#endif