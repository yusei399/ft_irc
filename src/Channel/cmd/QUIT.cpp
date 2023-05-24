#include "Client.hpp"
#include "ChannelManager.hpp"

void ChannelManager::remove_by_all_channel(Client &client)
{
	for(channel_it ch_it = channels.begin(); ch_it != channels.end(); ch_it++)
	{
		Channel &channel = const_cast<Channel&>(*ch_it);
		if (!channel.is_member(client))
			continue;
		channel.remove_client(client);
	}
}
