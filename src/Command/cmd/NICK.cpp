#include "CmdManager.hpp"

static bool require_valid_nick(Client &client, const std::string & new_nick)
{
	if (new_nick.size() > 9)
	{
		reply(client, ERR_ERRONEUSNICKNAME(client));
		return false;
	}
	if (client.exist_nickname(new_nick))
	{
		reply(client, ERR_NICKNAMEINUSE(client, new_nick));
		return false;
	}
	return true;
}

static void set_nick(Client& client, const std::string &new_nick, const Command& cmd, ChannelManager& channelManager)
{
	channelManager.cmd_reply_to_same_channel(client, cmd);
	reply(client, REP_CMD(client, cmd));
	client.set_nick(new_nick);
}

//NICK a : 自分のニックネームをaにする
void CmdManager::nick(Client &client, const Command& cmd)
{
	if (!require_authed(client)) return;
	if (!require_enough_params(client, cmd, 1, 2)) return;
	std::string new_nick = cmd._params[0];
	if (!require_valid_nick(client, new_nick)) return;
	//nickとuserを使わないとpass以外のコマンドが使えない
	if (!client.nickname_seted && client.user_seted)
	{
		set_nick(client, new_nick, cmd, channelManager);
		send_welcome_msgs(client);
	}
	else
	{
		set_nick(client, new_nick, cmd, channelManager);
	}
}
