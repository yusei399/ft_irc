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

