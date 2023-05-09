#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool require_valid_cmd(Client &client, const Command& cmd)
{
	if (cmd._params.size() != 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static bool require_yet_authed(Client &client)
{
	if (client.is_authed())
	{
		send_errmsg(client,462, ":You may not reregister");
		return false;
	}
	return true;
}

// PASS <server_password> : サーバーのパスワード認証を行う。
//							認証が行われていないとnick, user以外のコマンドが使えない
void ChannelManager::pass(Client &client, const Command& cmd, const std::string &server_pass)
{
	if (!require_yet_authed(client)) return;
	if (!require_valid_cmd(client, cmd)) return;
	const std::string &pass = cmd._params[0];
	if (pass != server_pass)
	{
		send_errmsg(client, 464, " :Password incorrect");
		return;
	}
	client.set_auth(true);
	send_msg(client, "Password correct!");//本家にはないが分かりにくいので、認証時メッセージを送る
}