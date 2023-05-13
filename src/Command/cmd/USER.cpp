#include "CmdManager.hpp"

static bool require_yet_set_user(Client &client)
{
	if (client.user_seted)
	{
		send_numeric_msg(client,462, ":You may not reregister");
		return false;
	}
	return true;
}

//USER <username> <hostname> <servername> :<realname>
void CmdManager::user(Client &client, const Command&cmd)
{
	if (!require_authed(client)) return;
	if (!require_enough_params(client, cmd, 3, 4, true)) return;
	if (!require_yet_set_user(client)) return;
	client.set_user_info(cmd._params[0], cmd._params[1], cmd._params[2], cmd._trailing);
	//nickとuserを使わないとpass以外のコマンドが使えない
	if (!client.user_seted && client.nickname_seted)
		send_msg(client, "001 "+client.get_nick() + " :Welcome to the Internet Relay Network " + client.get_nick());
		//send_msg(client, "001 :Welcome to the Internet Relay Network " + client.get_nick());
	client.user_seted = true;
}