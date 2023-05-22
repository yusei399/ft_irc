#include "CmdManager.hpp"
static std::vector<std::string> parse_ch_names(const Command& cmd)
{
	return split(cmd._params[0], ",");;
}
void CmdManager::part(Client& sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 1, 2))	return;
	std::vector<std::string> ch_names = parse_ch_names(cmd);
	channelManager.part_list(cmd, sender, ch_names);
}