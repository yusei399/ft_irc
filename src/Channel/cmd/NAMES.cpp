#include "Client.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static std::string get_names_str(const Channel &ch, const Client &client)
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

void Channel::names(const Client& sender) const
{
    if (!require_sender_is_member(sender))return;
    send_msg_past(sender, get_names_str(*this, sender));
	send_msg_past(sender, get_name()+ " :End of /NAMES list");
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
		get_channel(channels[i]).names(client);
	}
}