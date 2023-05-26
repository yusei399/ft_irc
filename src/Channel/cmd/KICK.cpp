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

//senderの権限でban_userをチャンネルから追い出す
void Channel::kick(const Command&cmd, Client &sender, Client& ban_user)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_in_channel(sender, ban_user, *this)) return;
	if (!require_operator(sender)) return;
	reply_cmd_all(sender, cmd);
	remove_client(ban_user);
}