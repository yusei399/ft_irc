#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool require_in_channel(Client &sender, Client& kick_user, Channel& channel)
{
	bool ok = true;
	if (!channel.require_target_is_member(sender, kick_user))ok = false;
	if (!channel.require_sender_is_member(sender))ok = false;
	return ok;
}

static void broadcast_kick_msg(Client &sender, Client& ban_user, const std::string & kick_reason, Channel &channel)
{
	std::string msg = sender.get_nick() + " has kicked " +ban_user.get_nick() +" from " +  channel.get_name();
    if (kick_reason != "")
		msg += " (" + kick_reason +")";
	channel.broadcast(sender, msg);
}

//<nick> has kicked <target> from <channel> (<reason>)
//senderの権限でban_userをチャンネルから追い出す
void Channel::kick(Client &sender, Client& ban_user, const std::string & kick_reason)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_in_channel(sender, ban_user, *this)) return;
	if (!require_operator(sender)) return;
	broadcast_kick_msg(sender, ban_user, kick_reason, *this);
	part(ban_user);
}
