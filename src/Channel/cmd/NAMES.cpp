#include "Client.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static std::string get_name_list(const Channel &ch, const Client &client)
{
	std::string msg = "";
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

/// @brief チャンネルに参加しているクライアントの一覧を出力
/// @param sender 
/// @param names_constraints コマンドの送信者がチャンネルに参加していない時にエラーを出すかどうか
void Channel::names(const Client& sender) const
{
   	reply(sender, RPL_NAMREPLY(sender, (this->get_name()), get_name_list(*this, sender)));
	reply(sender, RPL_ENDOFNAMES(sender, (this->get_name())));
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