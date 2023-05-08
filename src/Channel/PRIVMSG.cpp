#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"

static bool check_valid_param(const Client &client, const Command &cmd)
{
	bool is_ok = true;
	if (cmd._params.size() == 0)
	{
		send_errmsg(client, 411, ":No recipient given (" + cmd.get_original_str()+ ")");
		is_ok = false;
	}
	else if (cmd._params.size() > 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		is_ok = false;
	}
	if (cmd._trailing == "")
	{
		send_errmsg(client, 412, ":No text to send");
		is_ok = false;	
	}
	return is_ok;
}
/*
全体のパラメーター系
411 ERR_NORECIPIENT: メッセージの宛先が指定されていない場合に発生します。例: PRIVMSG :Hi
412 ERR_NOTEXTTOSEND: メッセージの内容が指定されていない場合に発生します。例: PRIVMSG alice

送るここのもの
401 ERR_NOSUCHNICK: 宛先となるユーザーが存在しない場合に発生します。例: PRIVMSG alice :Hi (aliceというユーザーがいない場合)
403 ERR_NOSUCHCHANNEL: 宛先となるチャンネルが存在しない場合に発生します。例: PRIVMSG #foo :Hi (#fooというチャンネルがいない場合)
404 ERR_CANNOTSENDTOCHAN: 宛先となるチャンネルにメッセージを送る権限がない場合に発生します。例: PRIVMSG #secret :Hi (#secretというチャンネルが招待制で自分が招待されていない場合)
442 ERR_NOTONCHANNEL: 自分が指定したチャンネルに参加していない場合に発生します。例: PRIVMSG #help :Hi (自分が#helpというチャンネルに参加していない場合)

	x 441 ERR_USERNOTINCHANNEL: 宛先となるユーザーが指定したチャンネルに参加していない場合に発生します。例: PRIVMSG alice #help :Hi (aliceというユーザーが#helpというチャンネルに参加していない場合)
	x 446 ERR_USERSDISABLED: ユーザーのリストを取得する機能が無効化されている場合に発生します。例: USERS (USERSコマンドがサーバーで無効化されている場合)
	x 451 ERR_NOTREGISTERED: 自分がサーバーに登録されていない場合に発生します。例: PRIVMSG alice :Hi (自分がサーバーに接続していない場合)
*/

static std::vector<std::string> parse_recievers(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static bool is_channel(const std::string &reicieve)
{
	return reicieve != "" && reicieve[0] == '#';
}

static void privmsg_to_channel(Client &client, const std::string &channel_name, const std::string& msg, const ChannelManager& chm)
{
	if (!chm.exist_channel(channel_name))
	{
		send_errmsg(client, 403, channel_name + " :No such channel");
		return;
	}
	chm.get_channel(channel_name).privmsg(client, msg);
}

static void privmsg_to_user(Client &sender, const std::string &reciever_name, const std::string& msg, std::map<int, Client> &connect_clients)
{
	//todo ClientManagerにまとめる
	for(std::map<int, Client>::iterator it = connect_clients.begin(); it != connect_clients.end(); it++)
	{
		if (it->second.get_nick() != reciever_name)
			continue;
		send_msg(it->second, ":" + sender.get_nick() +" PRIVMSG "+reciever_name +" :" + msg);
		return;
	}
	send_errmsg(sender, 403, reciever_name + " :No such channel");
}

void ChannelManager::privmsg(Client &client, const Command& cmd, std::map<int, Client> &connect_clients)
{
	if (!check_authenticated(client)) return;
	if (!check_seted_nick_user(client)) return;
	if (!check_valid_param(client, cmd)) return;
	std::string msg = cmd._trailing;
	std::vector<std::string> recievers = parse_recievers(cmd);
	for (size_t i = 0; i < recievers.size(); i++)
	{
		if (is_channel(recievers[i]))
			privmsg_to_channel(client, recievers[i], msg, *this);
		else
			privmsg_to_user(client, recievers[i], msg, connect_clients);
	}
	
}