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
	std::string flag = cmd._params[1];
    if (flag == "i")
        channel.send_mode_state_i(sender);
	else if (flag == "+i")
        channel.mode_i(sender, true);
    else if (flag == "-i")
        channel.mode_i(sender,  false);
    else if (flag == "+o" || flag == "-o")
	{
		std::string target_user = cmd._params[2];
		if (!clientManager.require_exist_nick(sender, target_user) )
			return;
		Client &target = clientManager.get_client_by_nick(target_user);
		if (flag == "+o")
		{
        	channel.mode_o(sender, true, target);
		}
		else
		{
        	channel.mode_o(sender, false, target);
		}
	}
    else
        send_errmsg(sender, 472, flag+ " :is unknown mode char to me");
}
