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

static void send_kick_msg(Client &sender, Client& ban_user, const std::string & kick_reason, Channel &channel)
{
	std::string msg = sender.get_nick() + " has kicked " +ban_user.get_nick() +" from " +  channel.get_name();
    if (kick_reason != "")
		msg += " (" + kick_reason +")";
	send_msg_past(sender, msg);
}

//<nick> has kicked <target> from <channel> (<reason>)
//senderの権限でban_userをチャンネルから追い出す
void Channel::kick(const Command&cmd, Client &sender, Client& ban_user, const std::string & kick_reason)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_in_channel(sender, ban_user, *this)) return;
	if (!require_operator(sender)) return;
	reply_cmd_all(sender, cmd);
	remove_client(ban_user);
}
/*
todo
送信者には、KICKが成功したことを示すRPL_KICKEDが送られます
KICKされた人間には、KICKされたことと、KICKしたユーザーとチャンネルと理由を示すKICKが送られます
その他のチャンネルの人間には、KICKされた人間と、KICKしたユーザーと理由を示すKICKが送られます

チャンネル#testで、オペレーターのAliceがユーザーのBobをKICKする場合、以下のようなメッセージが送られます。

Aliceには、RPL_KICKED :You have kicked Bob from #test (Bye bye!)が送られます。
Bobには、KICK #test Bob :Alice (Bye bye!)が送られます。
その他のチャンネルの人間には、KICK #test Bob :Alice (Bye bye!)が送られます。
この例でわかるように、KICKされた人間とその他のチャンネルの人間に送られるメッセージは同じ内容ですが、送信者が異なります。KICKされた人間にはサーバから、その他のチャンネルの人間にはオペレーターから送られます
*/