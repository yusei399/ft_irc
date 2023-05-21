#include "ChannelManager.hpp"


channel_it ChannelManager::find_it(std::string channelName) const
{
	for(channel_it it = channels.begin(); it != channels.end(); it++)
		if (it->get_name() == channelName)
			return it;
	return channels.end();
}

Channel& ChannelManager::get_channel(std::string channelName) const
{
	channel_it ch = find_it(channelName);
	if (ch == channels.end())
		throw std::logic_error("must not use ChanndlManager::find_must_exist(channelName) when not exist");
	return const_cast<Channel&>(*ch);
}

bool ChannelManager::exist_channel(std::string channelName) const
{
	return find_it(channelName) != channels.end();
}

void ChannelManager::privmsg_to_channel(Client &sender, const std::string &channel_name, const std::string & msg)
{
	if (!require_exist_channel(sender, channel_name))
		return;
	get_channel(channel_name).privmsg(sender, msg);
}

//クライアントが属するチャンネルを全て返す
/*
const std::set<Channel> ChannelManager::get_belong_channels(const Client &client)
{
	std::set<Channel> belongs;
	for(channel_it ch_it = channels.begin(); ch_it != channels.end(); ch_it++)
		if (ch_it->is_member(client))
			belongs.insert(*ch_it);
	return belongs;
}*/

bool ChannelManager::is_valid_channel_name(const std::string & channel_name)
{
	return !(channel_name == "" || channel_name[0] != '#' || channel_name == "#");
}

bool ChannelManager::require_valid_channel_name(Client &client, const std::string & channel_name)
{
	if (!(is_valid_channel_name(channel_name)))
	{
		reply(client, ERR_NOSUCHCHANNEL(client, channel_name));
		return false;
	}
	return true;
}

bool ChannelManager::require_exist_channel(Client &client, const std::string & channel_name)
{
	if (!exist_channel(channel_name))
	{
		reply(client, ERR_NOSUCHCHANNEL(client, channel_name));
		return false;
	}
	return true;
}

//todo
//参加時トピックと、namesを表示
void ChannelManager::join(Client &client, const std::vector<std::string> &ch_names, const std::vector<std::string> &ch_pass)
{
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!require_valid_channel_name(client, ch_names[i]))
			continue;
		if (exist_channel(ch_names[i]))
			get_channel(ch_names[i]).join(client, ch_pass[i]);
		else
		    channels.insert(Channel(ch_names[i], client, ch_pass[i]));
	}
}

//チャンネルから離脱する
//存在しないチャンネルが指定された場合 403エラー
void ChannelManager::try_part(std::string channelName, Client& client)
{
	if (!require_exist_channel(client, channelName))
		return;
	get_channel(channelName).part(client);
}

void ChannelManager::part_list(Client &sender, std::vector<std::string> &ch_names)
{
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!require_exist_channel(sender, ch_names[i]))
			continue;
		get_channel(ch_names[i]).part(sender);
	}
}
