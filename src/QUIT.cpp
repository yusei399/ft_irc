#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool require_enough_param(Client &client, const Command&cmd)
{
	if (cmd._params.size() != 0)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static void send_quit_msg(Client&sender, const Command &cmd, ClientManager &clientManager)
{
	std::vector<Client> recievers = clientManager.get_connect_clients();
	for (size_t i = 0; i < recievers.size(); i++)
	{
		if (recievers[i] == sender)
			continue;
		std::string msg =sender.get_nick()+" has quit";
		if (cmd._trailing == "") 
			send_msg(recievers[i], msg);
		else
			send_msg(recievers[i], msg + " (Quit: " + cmd._trailing + ")");
	}
}

void quit(Client&client, const Command &cmd, ClientManager &clientManager, ChannelManager& channelManager)
{
	if (!require_enough_param(client, cmd))
		return ;
	send_quit_msg(client, cmd, clientManager);
	channelManager.quit_all_channel(client, cmd._trailing);
	clientManager.erase_client(client);
}