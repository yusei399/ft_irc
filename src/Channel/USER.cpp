#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool is_enough_param(Client &client, const Command&cmd)
{
	if (cmd._params.size() != 3 || cmd._trailing == "")
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static bool is_already_set_user(Client &client)
{
	if (client.user_seted)
	{
		send_errmsg(client,462, ":You may not reregister");
		return false;
	}
	return true;
}

//USER <username> <hostname> <servername> :<realname>
void ChannelManager::user(Client &client, const Command&cmd)
{
	if (!is_authenticated(client)) return;
	if (!is_enough_param(client, cmd)) return;
	client.set_user_name(cmd._params[0]);
	client.set_host_name(cmd._params[1]);
	client.set_server_name(cmd._params[2]);
	client.set_real_name(cmd._trailing);
	//nickとuserを使わないとpass以外のコマンドが使えない
	if (!client.user_seted && client.nickname_seted)
		send_msg(client, "001 :Welcome to the Internet Relay Network " + client.get_nick());
	client.user_seted = true;
}