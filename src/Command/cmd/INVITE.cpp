#include "CmdManager.hpp"

void CmdManager::invite(Client& sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 2, 3))	return;
	std::string target_user_name = cmd._params[0];
	std::string channel_name = cmd._params[1];
	if (!clientManager.require_exist_nick(sender, target_user_name))return;
	if (!channelManager.require_exist_channel(sender, channel_name))return;
	Client& target_user = clientManager.get_client_by_nick(target_user_name);
	Channel& channel = channelManager.get_channel(channel_name);
	channel.invite(cmd, sender, target_user);
}
