#include "CmdManager.hpp"

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

void CmdManager::quit(Client&client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 1)) return ;
	send_quit_msg(client, cmd, clientManager);
	channelManager.quit_all_channel(client, cmd._trailing);
	clientManager.erase_client(client);
}