/*#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"*/
#include "CmdManager.hpp"

static bool require_valid_cmd(Client &client, const Command&cmd)
{
	if (cmd._params.size() > 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}


static void names_all_client(const Client &sender, ClientManager&clientManager)
{
	std::string msg;
	std::vector<Client> connect_clients = clientManager.get_connect_clients();
	for (size_t i = 0; i < connect_clients.size(); i++)
		msg += " " + connect_clients[i].get_nick();
	send_msg(sender,  msg);
	send_msg(sender, " :End of /NAMES list");
}

void CmdManager::names(Client &client, const Command& cmd,  ChannelManager &chm, ClientManager& clientManager)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_valid_cmd(client, cmd)) return;
	if (cmd._params.size() == 0)
		names_all_client(client, clientManager);
	else
		chm.names_channel(client, cmd, chm);
}