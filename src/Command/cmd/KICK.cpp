#include "CmdManager.hpp"


static bool require_enough_params(Client &client, const Command& cmd)
{
	if (cmd._params.size() != 2)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static bool require_exist_user(Client &client, const std::string& kick_user, ClientManager& clientManager)
{
	if (!clientManager.exist_client_by_nick(kick_user))
	{
		send_errmsg(client, 401, kick_user + " :No such nick");
		return false;
	}
	return true;
}

void CmdManager::kick(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd))	return;
	std::string channel_name = cmd._params[0];
	std::string kick_user_name = cmd._params[1];
	if (!channelManager.require_exist_channel(sender, channel_name))  return;
	if (!require_exist_user(sender, kick_user_name, clientManager))  return;
	Channel& channel = channelManager.get_channel(channel_name);
	Client &ban_user = clientManager.get_client_by_nick(kick_user_name);
	std::string kick_reason = cmd._params[0];
	channel.kick(sender, ban_user, kick_reason);
}
