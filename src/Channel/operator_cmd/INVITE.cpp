#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"
/*
INVITEコマンドは、チャンネルに招待された人しか入れないように設定されたチャンネル（+iモード）に、他のユーザーを招待するために使われます1。

INVITEコマンドの使い方は以下の通りです1。

INVITE <nickname> <channel>
ERR_NOSUCHCHANNEL: 指定したチャンネルが存在しない場合に発生します。チャンネル名を正しく入力してください。
ERR_NOTONCHANNEL: 招待しようとしたチャンネルに自分が参加していない場合に発生します。自分が参加しているチャンネルに対してのみINVITEコマンドを使えます。
ERR_USERONCHANNEL: 招待しようとしたユーザーがすでにそのチャンネルに参加している場合に発生します。別のユーザーを招待してください。
ERR_CHANOPRIVSNEEDED: 自分がオペレーター権限を持っていないチャンネルでINVITEコマンドを使おうとした場合に発生します。オペレーター権限を持っているチャンネルに対してのみINVITEコマンドを使えます。
INVITEコマンドに関して他に何か知りたいことはありますか？
*/

static bool require_enough_params(Client &client, const Command& cmd)
{
	if (cmd._params.size() != 2)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static bool require_valid_user(Client &client, const std::string& user, ClientManager& clientManager)
{
	if (!clientManager.exist_client_by_nick(user))
	{
		send_errmsg(client, 401, user + " :No such nick");
		return false;
	}
	return true;
}

static bool require_valid_channel(Client &client, const std::string& channel_name, ChannelManager& channelManager)
{
	if (!channelManager.exist_channel(channel_name))
	{
		send_errmsg(client, 403, channel_name + " :No such channel");
		return false;
	}
	return true;
}

void invite(Client& sender, Command& cmd, ChannelManager& channelManager, ClientManager &clientManager)
{
	if (!require_enough_params(sender, cmd))	return;
	std::string target_user_name = cmd._params[0];
	std::string channel_name = cmd._params[1];
	if (!require_valid_user(sender, target_user_name, clientManager))return;
	if (!require_valid_channel(sender, channel_name, channelManager))return;
	Client& target_user = clientManager.get_client_by_nick(target_user_name);
	Channel& channel = channelManager.get_channel(channel_name);
	channel.invite(sender, target_user);
//	const std::string &target_user, const std::string & channel_name
}



void Channel::invite(Client &sender, Client& target)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_operator(sender)) return;
			
}