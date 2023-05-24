#include "Channel.hpp"

static bool require_not_member(Client& sender, Client& target, Channel& channel)
{
	if (channel.is_member(target))
	{
        reply(sender, ERR_USERONCHANNEL(sender, target, channel));
		return false;
	}
	return true;
}

void Channel::invite(const Command &cmd, Client &sender, Client& target)
{
	if (!require_operator(sender)) return;
	if (!require_not_member(sender, target, *this)) return;
	invited.insert(target);
	reply(sender, RPL_INVITING(sender, target, (*this)));
	reply(target, REP_CMD(sender, cmd));
}