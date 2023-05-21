#include "CmdManager.hpp"


static bool require_valid_nick(Client &client, const std::string & new_nick)
{
	if (new_nick.size() > 9)
	{
		send_msg(client, ERR_ERRONEUSNICKNAME(client));
		return false;
	}
	if (client.exist_nickname(new_nick))
	{
		send_msg(client, ERR_NICKNAMEINUSE(client, new_nick));
		return false;
	}
	return true;
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
		client.set_nick(new_nick);
		send_welcome_msgs(client);
	}
	else
	{
		client.set_nick(new_nick);
	}
}
