#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"


static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static void send_client_list(Channel ch, const Client &client)
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
	send_msg(client,  msg);
	send_msg(client, ch.get_name()+ " :End of /NAMES list");
}

//NAMES       : 全てのクライアントを表示
//NAMES #a,#b : #a,#bチャンネルに所属するクライアントを表示
//オペレーターは名前の先頭に@がつく
void ChannelManager::names_channel(Client &client, const Command& cmd,  ChannelManager &chm)
{
	std::vector<std::string> channels = parse_channels(cmd);
	for (size_t i = 0; i < channels.size(); i++)
	{	
		if (chm.exist_channel(channels[i]))
			send_client_list(chm.get_channel(channels[i]), client);
      	else
      	  	send_errmsg(client, 403, channels[i] + " :No such channel");
	}
}