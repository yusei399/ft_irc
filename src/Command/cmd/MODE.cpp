#include "CmdManager.hpp"

static bool require_enough_params(Client &sender, const Command& cmd)
{
	if (cmd._params.size() < 2)
	{
		send_errmsg(sender, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

void CmdManager::mode(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd))	return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	channel.mode(sender, cmd._params[1]);
}
