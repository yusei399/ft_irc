#include "CmdManager.hpp"
#include "Mode.hpp"

void CmdManager::mode_i(Channel &channel, Client &sender, const Command &cmd)
{
	std::string flag = get_flag(cmd);
	if (flag == MODE_I)
		channel.mode_i_state(sender);
	else if (flag == MODE_I_ADD)
		channel.mode_i(cmd, sender, true);
	else if (flag == MODE_I_REM)
		channel.mode_i(cmd, sender, false);
	else
		throw std::logic_error("");
}

void CmdManager::mode_o(Channel &channel, Client &sender, const Command &cmd)
{
	if (!require_enough_params(sender, cmd, 3, 6))
		return;
	std::string flag = get_flag(cmd);
	std::string target_nick = cmd._params[2];
	if (!clientManager.require_exist_nick(sender, target_nick))
		return;
	Client &target = clientManager.get_client_by_nick(target_nick);
	if (flag == MODE_O_ADD)
		channel.mode_o(cmd, sender, true, target);
	else if (flag == MODE_O_REM)
		channel.mode_o(cmd, sender, false, target);
	else
		throw std::logic_error("");
}

void CmdManager::mode_t(Channel &channel, Client &sender, const Command &cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))
		return;
	std::string flag = get_flag(cmd);
	if (flag == MODE_T)
		channel.mode_t_state(sender);
	else if (flag == MODE_T_ADD)
		channel.mode_t(cmd, sender, true);
	else if (flag == MODE_T_REM)
		channel.mode_t(cmd, sender, false);
	else
		throw std::logic_error("");
}

void CmdManager::mode_k(Channel &channel, Client &sender, const Command &cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))
		return;
	std::string flag = get_flag(cmd);
	if (flag == MODE_K)
		channel.mode_k_state(sender);
	else if (flag == MODE_K_ADD)
	{
		if (!require_enough_params(sender, cmd, 3, 6))
			return;
		channel.mode_k_add(cmd, sender, cmd._params[2]);
	}
	else if (flag == MODE_K_REM)
	{
		// 2つ channel, flag
		channel.mode_k_rem(cmd, sender);
	}
	else
		throw std::logic_error("");
}

void CmdManager::mode_l(Channel &channel, Client &sender, const Command &cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))
		return;
	std::string flag = get_flag(cmd);
	if (flag == MODE_L)
		channel.mode_l_state(sender);
	else if (flag == MODE_L_ADD)
	{
		if (!require_enough_params(sender, cmd, 3, 6))
			return;
		channel.mode_l_add(cmd, sender, cmd._params[2]);
	}
	else if (flag == MODE_L_REM)
	{
		// 2つ channel, flag
		channel.mode_l_rem(cmd, sender);
	}
	else
		throw std::logic_error("");
}

void CmdManager::mode_state(Channel &channel, Client &sender)
{
	std::string mode = channel.get_mode();
	reply(sender, RPL_CHANNELMODEIS(sender, channel, mode, ""));
}

// todoリファクタ
void CmdManager::mode(Client &sender, const Command &cmd)
{
	if (!require_authed(sender))
		return;
	if (!require_nick_user(sender))
		return;
	if (!require_enough_params(sender, cmd, 1))
		return;
	if (!channelManager.is_valid_channel_name(cmd._params[0]))
		return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0]))
		return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	if (cmd._params.size() == 1)
		mode_state(channel, sender);
	else if (is_mode_i(cmd))
		mode_i(channel, sender, cmd);
	else if (is_mode_o(cmd))
		mode_o(channel, sender, cmd);
	else if (is_mode_t(cmd))
		mode_t(channel, sender, cmd);
	else if (is_mode_k(cmd))
		mode_k(channel, sender, cmd);
	else if (is_mode_l(cmd))
		mode_l(channel, sender, cmd);
	else
		reply(sender, ERR_NOCHANMODES(sender, get_flag(cmd)));
}
// MODE #channel option [target_user]
