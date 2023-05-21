
#include "CmdManager.hpp"

static void names_all_client(const Client &sender, ClientManager&clientManager)
{
	std::string msg;
	std::vector<Client> connect_clients = clientManager.get_connect_clients();
	for (size_t i = 0; i < connect_clients.size(); i++)
		msg += " " + connect_clients[i].get_nick();
	send_msg_past(sender,  msg);
	send_msg_past(sender, " :End of /NAMES list");
}

void CmdManager::names(Client &client, const Command& cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 2)) return;
	if (cmd._params.size() == 0)
		names_all_client(client, clientManager);
	else
		channelManager.names_channel(client, cmd);
}