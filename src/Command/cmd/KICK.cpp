#include "CmdManager.hpp"

//KICK #channel nick
void CmdManager::kick(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 2, 3))	return;
	std::string channel_name = cmd._params[0];
	std::string kick_user_name = cmd._params[1];
	if (!channelManager.require_exist_channel(sender, channel_name))  return;
	if (!clientManager.require_exist_nick(sender, kick_user_name))  return;
	Channel& channel = channelManager.get_channel(channel_name);
	Client &ban_user = clientManager.get_client_by_nick(kick_user_name);
	channel.kick(cmd, sender, ban_user);
}
