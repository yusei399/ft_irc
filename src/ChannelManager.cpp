#include "../include/ChannelManager.hpp"

ChannelManager::ChannelManager() {}


//見つからなかったらchannels.end()を返す
channel_it ChannelManager::find_channel(std::string channelName)
{
	return channels.find(Channel(channelName));
}

bool ChannelManager::exist_channel(std::string channelName)
{
	return find_channel(channelName) != channels.end();
}

// チャンネルが存在しなければ新しく作成する
void ChannelManager::join(std::string channelName, const Client &client)
{
    if (exist_channel(channelName))
	{
		const_cast<Channel&> (*find_channel(channelName)).join(client);
	}
	else
	{
	    channels.insert(Channel(channelName, client));
	}
}

//チャンネルから離脱する
//存在しないチャンネルが指定された場合 403エラー
void ChannelManager::try_part(std::string channelName, const Client& client)
{
	if (exist_channel(channelName))
	{
		const_cast<Channel&> (*find_channel(channelName)).try_part(client);
	}
	else
	{
        send_errmsg(client, 403, channelName + " :No such channel");
	}
}