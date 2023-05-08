#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool is_enough_param(Client &client, const Command&cmd)
{
	if (cmd._params.size() != 0)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static void send_quit_msg(Client&client, const Command &cmd, ClientManager &clientManager)
{
	for (std::map<int, Client>::iterator it = clientManager._connect.begin(); it != clientManager._connect.end(); it++)
	{
		Client receiver = it->second;
		if (receiver == client)
			continue;
		std::string msg =client.get_nick()+" has quit";
		if (cmd._trailing == "") 
			send_msg(receiver, msg);
		else
			send_msg(receiver, msg + " (Quit: " + cmd._trailing + ")");
	}
}

void quit(Client&client, const Command &cmd, ClientManager &clientManager, ChannelManager& channelManager)
{
	if (!is_enough_param(client, cmd))
		return ;
	send_quit_msg(client, cmd, clientManager);
	channelManager.quit_channels(client, cmd._trailing);
	clientManager.erase_client(client);
}