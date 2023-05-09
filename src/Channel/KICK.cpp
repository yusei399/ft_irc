#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

/*
KICK <channel> <nick> [<reason>]
<channel>: ユーザーを追い出すチャンネルの名前
<nick>: 追い出すユーザーのニックネーム
<reason>: 追い出す理由（オプション）
パラメーターはスペースで区切って渡します。理由にスペースが含まれる場合は、コロンで始めます。

例: KICK #test user1 :spamming

起きうるエラーは以下の通りです。

401 ERR_NOSUCHNICK: 指定したニックネームのユーザーが存在しない場合

442 ERR_NOTONCHANNEL: 自分が指定したチャンネルに参加していない場合
482 ERR_CHANOPRIVSNEEDED: 自分が指定したチャンネルのオペレーターでない場合
*/
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

//<nick> has kicked <target> from <channel> (<reason>)
void Channel::kick(Client &operator_user, Client& kicked_user, const std::string & kick_reason)
{
	if (!is_authenticated(operator_user)) return;
	if (!is_seted_nick_user(operator_user)) return;
	if (!is_in_channel(operator_user, kicked_user, *this))	return;
	if (!is_operator_user(operator_user, *this)) return;
	std::string msg = operator_user.get_nick() + " has kicked " +kicked_user.get_nick() +" from " +  get_name();
    if (kick_reason != "")
		msg += " (" + kick_reason +")";
	broadcast(operator_user, msg);
	try_part(kicked_user);
}


/*
void ChannelManager::kick(Client &operator, Channel channel, Client kick_user)
{

}*/