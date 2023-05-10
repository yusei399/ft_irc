#ifndef CMD_MANAGER_HPP
#define CMD_MANAGER_HPP
#include "ClientManager.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

class CmdManager
{
	ClientManager &clientManager;
	ChannelManager &channelManager;
	std::string server_pass;
public:
	CmdManager(ClientManager &clientManager, ChannelManager &channelManager, const std::string &server_pass) :clientManager(clientManager), channelManager(channelManager), server_pass(server_pass){};
	void exe_cmd(Client &sender, const Command &cmd);
	
	

void join(Client &client, const Command &cmd);
void pass(Client &client, std::string const &passwprd);
void user(Client &client);
	//void cap(Client &client);
	void quit(Client&client, const Command &cmd);
	void names(Client &client, const Command& cmd);
	//void PONG(Client &client, std::vector<std::string> &server_name);
	void privmsg(Client& client, const Command &cmd);
	void kick(Client &client, const Command& cmd);
	void invite(Client& sender, const Command& cmd);
};

#endif // CMD_MANAGER_HPP