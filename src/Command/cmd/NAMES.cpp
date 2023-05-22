
#include "CmdManager.hpp"

void CmdManager::names_all_channel(Client &client, const Command& cmd)
{
	std::vector<Client> recievers = clientManager.get_connect_clients();
	std::set<Client> recievers_set(recievers.begin(), recievers.end());
	channelManager.names_all(client, cmd, recievers_set);
}

void CmdManager::names(Client &client, const Command& cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 2)) return;
	if (cmd._params.size() == 0)
		names_all_channel(client, cmd);
	else
		channelManager.names_channel(client, cmd);
}