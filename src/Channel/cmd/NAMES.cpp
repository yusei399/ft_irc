#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"


static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static std::string get_msg(Channel ch, const Client &client)
{
	std::string msg = ch.get_name() + " :";
	for(std::set<Client>::iterator cl_it = ch.get_members().begin(); cl_it != ch.get_members().end(); cl_it++)
	{
		if (cl_it != ch.get_members().begin())
			msg += " ";
		if (ch.is_operator(*cl_it))
			msg+="@";
		msg += cl_it->get_nick();
	}
	return msg;
}

static void send_client_list(Channel ch, const Client &client)
{
	send_msg(client,  get_msg(ch, client));
	send_msg(client, ch.get_name()+ " :End of /NAMES list");
}

//NAMES       : 全てのクライアントを表示
//NAMES #a,#b : #a,#bチャンネルに所属するクライアントを表示
//オペレーターは名前の先頭に@がつく
void ChannelManager::names_channel(Client &client, const Command& cmd)
{
	std::vector<std::string> channels = parse_channels(cmd);
	for (size_t i = 0; i < channels.size(); i++)
	{	
		if (!require_exist_channel(client, channels[i]))
			continue;
		send_client_list(get_channel(channels[i]), client);
	}
}