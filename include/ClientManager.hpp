#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Client.hpp"

//Client全体に対する操作を担う
class ClientManager
{
public:
	std::map<int, Client> _connect;
	void connect_client(int socketfd);
	Client& get_client_by_fd(int fd);
	std::map<int, Client>::iterator find_client_by_nick(const std::string & nick);
	bool exist_client_by_nick(const std::string &nickname);
	Client& get_client_by_nick(const std::string &nickname);
	void privmsg(Client &sender, const std::string &reciever_name, const std::string& msg);
	void erase_client(Client &client);
};


#endif // CLIENTMANAGER_HPP