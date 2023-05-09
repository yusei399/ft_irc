#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool is_in_channel(Client &operator_user, Client& kick_user, Channel& channel)
{
	bool ok = true;
	if (!channel.is_member(kick_user))
	{
		send_errmsg(operator_user, 441, kick_user.get_nick()+ " " +channel.get_name() + " :They aren't on that channel");
		ok = false;
	}
	if (!channel.is_member(operator_user))
	{
		send_errmsg(operator_user, 442, channel.get_name() + " :You're not on that channel");
		ok = false;
	}
	return ok;
}

static bool is_operator_user(Client& operator_user, Channel& channel)
{
	if (!channel.is_operator(operator_user))
	{
		send_errmsg(operator_user, 482, channel.get_name()+ " :You're not channel operator");
		return false;
	}
	return true;
}

static void broadcast_kick_msg(Client &operator_user, Client& ban_user, const std::string & kick_reason, Channel &channel)
{
	std::string msg = operator_user.get_nick() + " has kicked " +ban_user.get_nick() +" from " +  channel.get_name();
    if (kick_reason != "")
		msg += " (" + kick_reason +")";
	channel.broadcast(operator_user, msg);
}

//<nick> has kicked <target> from <channel> (<reason>)
//operator_userの権限でban_userをチャンネルから追い出す
void Channel::kick(Client &operator_user, Client& ban_user, const std::string & kick_reason)
{
	if (!is_authenticated(operator_user)) return;
	if (!is_seted_nick_user(operator_user)) return;
	if (!is_in_channel(operator_user, ban_user, *this))	return;
	if (!is_operator_user(operator_user, *this)) return;
	broadcast_kick_msg(operator_user, ban_user, kick_reason, *this);
	try_part(ban_user);
}
