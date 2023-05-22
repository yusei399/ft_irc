#include "CmdManager.hpp"

static bool require_valid_param(Client &client, const Command &cmd, CmdManager &cmdManager)
{
	bool is_ok = true;
	if (cmd._params.size() == 0)
	{
		reply(client, ERR_NORECIPIENT(client, cmd.get_original_str()));
		is_ok = false;
	}
	else if (!cmdManager.require_enough_params(client, cmd, 1, 2))
	{
		is_ok = false;
	}
	if (!cmd.has_trailing())
	{
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

void CmdManager::privmsg(Client& client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_valid_param(client, cmd, *this)) return;
	std::vector<std::string> targets = parse_targets(cmd);
	for (size_t i = 0; i < targets.size(); i++)
	{
		if (is_channel(targets[i]))
			channelManager.privmsg_to_channel(cmd, client, targets[i], cmd._trailing);
		else
			clientManager.privmsg(client, targets[i], cmd._trailing);
	}
}