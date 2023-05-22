#include "CmdManager.hpp"

void CmdManager::topic(Client& sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 1, 2)) return;
	std::string channel_name = cmd._params[0];
	if (!channelManager.require_exist_channel(sender, channel_name)) return;
	Channel &channel = channelManager.get_channel(channel_name);
	if (cmd.has_trailing())
		channel.set_topic(cmd, sender, cmd._trailing);
	else 
		channel.show_topic(sender);
}