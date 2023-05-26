#include "CmdManager.hpp"

static const std::string& channel_name(const Command& cmd)
{
	return cmd._params[0];
}

static void send_who_reply(Client &sender, Channel& channel)
{
	std::set<Client> members = channel.get_members();
	for(client_it it = members.begin(); it != members.end(); it++)
		reply(sender, RPL_WHOREPLY(sender, channel, (*it)));
	reply(sender, RPL_ENDOFWHO(sender, channel));;
}

void CmdManager::who(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 1, 2))	return;
	if (!channelManager.require_exist_channel(sender, channel_name(cmd))) return;
	send_who_reply(sender, channelManager.get_channel(channel_name(cmd)));
}
