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
#include "Command.hpp"
#include "ChannelManager.hpp"

//Client全体に対する操作を担う
class ClientManager
{
	std::map<int, Client> _connect;
public:
	void connect_client(int socketfd);
	std::map<int, Client>::iterator find_client_by_nick(const std::string & nick);
	Client& get_client_by_fd(int fd);
	Client& get_client_by_nick(const std::string &nickname);
	const std::vector<Client> get_connect_clients();
	bool exist_client_by_nick(const std::string &nickname);
	bool require_exist_nick(Client& sender, const std::string &target_nick);
	void privmsg(const Command&cmd, Client &sender, const std::string &reciever_name, const std::string& msg);
	void erase_client(Client &client, ChannelManager& channelManager);

};


#endif // CLIENTMANAGER_HPP