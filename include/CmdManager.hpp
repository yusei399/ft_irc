#ifndef CMD_MANAGER_HPP
#define CMD_MANAGER_HPP
#include "ClientManager.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

class CmdManager
{
public:
void join(Client &client, const Command &cmd, ChannelManager &channelManager);
void pass(Client &client, std::string const &passwprd);
void user(Client &client);
	//void cap(Client &client);
	void quit(Client&client, const Command &cmd, ClientManager &clientManager, ChannelManager& channelManager);	
	void names(Client &client, const Command& cmd,  ChannelManager &chm, ClientManager& clientManager);
	//void PONG(Client &client, std::vector<std::string> &server_name);
	void privmsg(Client& client, const Command &cmd, ClientManager& clientManager, ChannelManager& channelManager);	
	void kick(Client &client, const Command& cmd, ClientManager& client_manager, ChannelManager& channel_manager);
	void invite(Client& sender, const Command& cmd, ClientManager &clientManager, ChannelManager& channelManager);
};

#endif // CMD_MANAGER_HPP