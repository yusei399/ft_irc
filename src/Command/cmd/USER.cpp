#include "CmdManager.hpp"

static bool require_yet_set_user(Client &client)
{
	if (client.user_seted)
	{
		reply(client, ERR_ALREADYREGISTRED(client));
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
		send_welcome_msgs(client);
	client.user_seted = true;
}