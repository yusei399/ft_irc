#include "CmdManager.hpp"

enum e_reply_require{recv_reply, not_recv_reply};
static bool require_valid_param(Client &client, const Command &cmd, CmdManager &cmdManager, e_reply_require reply_require)
{
	bool is_ok = true;
	if (cmd._params.size() == 0)
	{
		if(reply_require == recv_reply)
			reply(client, ERR_NORECIPIENT(client, cmd.get_original_str()));
		is_ok = false;
	}
	else if (!cmdManager.require_enough_params(client, cmd, 1, 2))
	{
		is_ok = false;
	}
	if (!cmd.has_trailing())
	{
		if(reply_require == recv_reply)
			reply(client, ERR_NOTEXTTOSEND(client));
		is_ok = false;	
	}
	return is_ok;
}



static std::vector<std::string> parse_targets(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static bool is_channel(const std::string &reicieve)
{
	return reicieve != "" && reicieve[0] == '#';
}

//PRIVMSG #a :msg
void CmdManager::privmsg(Client& client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_valid_param(client, cmd, *this, recv_reply)) return;
	std::vector<std::string> targets = parse_targets(cmd);
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (is_channel(targets[i]))
			channelManager.privmsg_to_channel(cmd, client, targets[i]);
		else
			clientManager.privmsg(cmd, client, targets[i]);
	}
}

/// @brief noticeはエラーがあっても返信しない
/// @param sender 
/// @param cmd 
void CmdManager::notice(Client &sender, const Command& cmd)
{
	if (!sender.is_authed()) return;
	if (!sender.user_seted || !sender.nickname_seted)return;
	if (!require_valid_param(sender, cmd, *this, not_recv_reply)) return;
	std::vector<std::string> targets = parse_targets(cmd);
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (is_channel(targets[i]))
			channelManager.notice_to_channel(cmd, sender, targets[i]);
		else
			clientManager.notice(cmd, sender, targets[i]);
	}
}