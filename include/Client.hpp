#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class Client
{
private:
	int _fd;
	std::string _nick;
//	std::string _command_name;
//	std::vector<std::string> _params;
//	bool _permission;
	//std::string _user;
	std::string _real_name;
	std::string _hostname;

public:
	Client(/* args */);
	Client(int fd, const std::string &nc);
	~Client();
//	void command_parser(std::string &command);
//	void preprocessing(const std::string &message, int &i);
//	void set_permission(bool permission) {_permission = permission;}
//	void processingparams(const std::string &message, int &i);
//	const std::string &get_cmd() const {return _command;}
//	const std::vector<std::string> &get_params() const {return _params;}
	int get_fd() const;
	std::string get_nick() const;
	std::string get_real_name() const;
	std::string get_host_name() const;
	void set_nick(const std::string &nick) {_nick = nick;}
	//void set_user(const std::string &user) {_user = user;}
	void set_real_name(const std::string &real_name) {_real_name = real_name;}
	void set_hostname(const std::string &hostname) {_hostname = hostname;}
//	void send_err_msg(int err_code, const std::string &message) const;
	bool operator<(const Client& rhs) const;
	bool operator==(const Client& rhs) const;
	bool operator!=(const Client& rhs) const;
};

//デバッグ用
std::ostream& operator<<(std::ostream& os, const Client& client);
//void send_message(const std::string &message, int fd, int flag);
#endif