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
	void mode_i(Client&sender, const Command&cmd);
	void mode_o(Client&sender, const Command&cmd);
public:
	CmdManager(ClientManager &clientManager, ChannelManager &channelManager, const std::string &server_pass) :clientManager(clientManager), channelManager(channelManager), server_pass(server_pass){};
	bool require_enough_params(Client &sender, const Command& cmd, size_t ok_min, size_t ng_min, bool require_trailing = false);
	
	std::vector<Command> parse_commands(const std::string &commands_msg);
	void exe_cmd(Client &sender, const Command &cmd);
	void join(Client &client, const Command &cmd);
	void pass(Client &client, const Command& cmd);
	void nick(Client &client, const Command& cmd);
	void user(Client &client, const Command &cmd);
	//void cap(Client &client);
	void quit(Client&client, const Command &cmd);
	void names(Client &client, const Command& cmd);
	void mode(Client &client, const Command& cmd);
	//void PONG(Client &client, std::vector<std::string> &server_name);
	void privmsg(Client& client, const Command &cmd);
	void kick(Client &client, const Command& cmd);
	void invite(Client& sender, const Command& cmd);
};

#endif // CMD_MANAGER_HPP