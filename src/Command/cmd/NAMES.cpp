
#include "CmdManager.hpp"

void CmdManager::names_all_channel(Client &client)
{
	std::vector<Client> recievers = clientManager.get_connect_clients();
	std::set<Client> recievers_set(recievers.begin(), recievers.end());
	channelManager.names_all(client, recievers_set);
}

//NAMES #a　指定したチャンネルに属するユーザーを表示
//NAMES		全てのチャンネルについて属するユーザーを表示、どのチャンネルにも属さないユーザーはチャンネル名を*として表示
void CmdManager::names(Client &client, const Command& cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 2)) return;
	if (cmd._params.size() == 0)
		names_all_channel(client);
	else
		channelManager.names_channel(client, cmd);
}