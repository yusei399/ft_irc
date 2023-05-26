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

/// @brief pdfによると、ユーザーに対してのMODEコマンドは実装しなくていいので無視する
/// @param channel_name 
/// @return 
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



/// @brief senderと同じチャンネルに属すクライアントを返す
/// @param sender 
/// @param channelManager 
/// @return 
std::set<Client> ChannelManager::get_same_channel_clients(Client&sender)
{
	std::set<Client> clients;
	std::set<Channel> channels = get_all_channels();
	for(channel_it it = channels.begin(); it != channels.end(); it++)
	{
		const Channel &channel = *it;
		if (channel.is_member(sender))
			clients.insert(channel.get_members().begin(), channel.get_members().end());
	}
	return clients;
}

/// @brief 同じチャンネルに属す全てのクライアントにコマンドのリプライをする, 送り手には返さない
void ChannelManager::cmd_reply_to_same_channel(Client&sender, const Command &cmd)
{
	const std::set<Client> &recievers = get_same_channel_clients(sender);
	for (client_it it = recievers.begin(); it != recievers.end(); ++it)
	{
		Client reciever = *it;
    	if (reciever == sender)
			continue;
		reply(reciever, REP_CMD(sender, cmd));
	}
}
