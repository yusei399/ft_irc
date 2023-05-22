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

void Channel::invite(Client &sender, Client& target)
{
	if (!require_operator(sender)) return;
	if (!require_not_member(sender, target, *this)) return;
	invited.insert(target);
	send_msg_past(target, sender.get_nick() + " invites you to join " + get_name());
}