#include "CmdManager.hpp"


static bool require_valid_nick(Client &client, const std::string & new_nick)
{
	if (new_nick.size() > 9)
	{
		send_numeric_msg(client, 432, ":Erroneus nickname");
		return false;
	}
	if (client.exist_nickname(new_nick))
	{
		send_numeric_msg(client,433, new_nick + " :Nickname is already in use" );
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
		//:irc.example.com 001 kaou :Welcome to the Internet Relay Network kaou
		send_msg(client, "001 "+new_nick + " :Welcome to the Internet Relay Network " + client.get_nick());
	}
	else
	{
		client.set_nick(new_nick);
	}
}
