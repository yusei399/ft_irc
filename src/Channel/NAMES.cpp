#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

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

static void reply_channel_client_list(Channel ch, const Client &client)
{
	std::string msg = ch.get_channel_name() + " :";
	for(std::set<Client>::iterator cl_it = ch.get_members().begin(); cl_it != ch.get_members().end(); cl_it++)
	{
		if (cl_it != ch.get_members().begin())
			msg += " ";
		if (ch.is_operator(*cl_it))
			msg+="@";
		msg += cl_it->get_nick();
	}
	send_msg(client,  msg);
	send_msg(client, ch.get_channel_name()+ " :End of /NAMES list");
}

static void reply_client_list(std::map<int, Client> connect_clients, const Client &client)
{
	std::string msg;
	for(std::map<int, Client> ::iterator cl_it = connect_clients.begin(); cl_it != connect_clients.end(); cl_it++)
	{
		msg += " " + cl_it->second.get_nick();
	}
	send_msg(client,  msg);
	send_msg(client, " :End of /NAMES list");
}

//指定されたチャンネルに属するクライアントを全て表示する
//オペレーターは名前の先頭に@がつく
void ChannelManager::names(Client &client, const Command& cmd,  ChannelManager &chm, std::map<int, Client> connect_clients)
{
	if (!check_authenticated(client)) return;
	if (!check_seted_nick_user(client)) return;
	if (!is_valid_cmd(client, cmd)) 
		return;
	if (cmd._params.size() == 0)
	{
		reply_client_list(connect_clients, client);
		return;
	}
	std::vector<std::string> channels = parse_channels(cmd);
	for (size_t i = 0; i < channels.size(); i++)
	{	
		if (chm.exist_channel(channels[i]))
			reply_channel_client_list(chm.get_channel(channels[i]), client);
      	else
      	  	send_errmsg(client, 403, channels[i] + " :No such channel");
	}
}