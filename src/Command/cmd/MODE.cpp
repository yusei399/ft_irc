#include "CmdManager.hpp"
#include "Mode.hpp"

void CmdManager::mode_i(Client&sender, const Command&cmd)
{
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_I)
        channel.mode_i_state(sender);
	else if (flag == MODE_I_ADD)
        channel.mode_i(sender, true);
    else if (flag == MODE_I_REM)
        channel.mode_i(sender,  false);
	else
		throw std::logic_error("");
}

void CmdManager::mode_o(Client&sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 3, 6))return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	std::string target_nick = cmd._params[2];
	if (!clientManager.require_exist_nick(sender, target_nick) )
		return;
	Client &target = clientManager.get_client_by_nick(target_nick);
	if (flag == MODE_O_ADD)
       	channel.mode_o(sender, true, target);
	else if(flag == MODE_O_REM)
       	channel.mode_o(sender, false, target);
	else
		throw std::logic_error("");
}

void CmdManager::mode_t(Client&sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_T)
		channel.mode_t_state(sender);
	else if (flag == MODE_T_ADD)
		channel.mode_t(sender, true);
	else if (flag == MODE_T_REM)
		channel.mode_t(sender, false);
	else
		throw std::logic_error("");
	///mode #channel +t
}

void CmdManager::mode(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 2, 6))	return;
	if (is_mode_i(cmd))
		mode_i(sender, cmd);
    else if (is_mode_o(cmd))
		mode_o(sender, cmd);
	else if (is_mode_t(cmd))
		mode_t(sender, cmd);
	else
        send_numeric_msg(sender, 472, get_flag(cmd)+ " :is unknown mode char to me");
}
