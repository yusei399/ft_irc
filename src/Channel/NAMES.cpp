#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"

static bool is_valid_cmd(Client &client, const Command&cmd)
{
	if (cmd._params.size() > 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static void reply_clients_list(Channel ch, const Client &client)
{
	std::string msg = ch.get_channel_name() + " :";
	for(std::set<Client>::iterator cl_it = ch.get_members().begin(); cl_it != ch.get_members().end(); cl_it++)
	{
		if (ch.is_operator(client))
			msg+=" @";
		else
			msg += " ";
	}
	send_msg(client,  msg);
	send_msg(client, ch.get_channel_name()+ " :End of /NAMES list");
}

//指定されたチャンネルに属するクライアントを全て表示する
//オペレーターは名前の先頭に@がつく
void ChannelManager::names(Client &client, const Command& cmd,  ChannelManager &chm, std::map<int, Client> connect_clients)
{
	if (!is_valid_cmd(client, cmd)) 
		return;
	std::vector<std::string> channels = parse_channels(cmd);
	for (size_t i = 0; i < channels.size(); i++)
	{	
		if (!chm.exist_channel(channels[i]))
		{
			send_msg(client, channels[i]+ " :No such channel");
			continue;
		}
		reply_clients_list(chm.get_channel(channels[i]), client);
	}
}