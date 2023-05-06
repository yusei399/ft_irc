#include "ChannelManager.hpp"


channel_it ChannelManager::find_it(std::string channelName) const
{
	for(channel_it it = channels.begin(); it != channels.end(); it++)
	{
		if (it->get_channel_name() == channelName)
		{
			return it;
		}
	}
	return channels.end();
}



///	存在しないチャンネルをgetしようとするとエラーが起きる
Channel& ChannelManager::get_channel(std::string channelName) const
{
	channel_it ch = find_it(channelName);
	if (ch == channels.end())
	{
		throw std::logic_error("must not use ChanndlManager::find_must_exist(channelName) when not exist");
	}
	return const_cast<Channel&>(*ch);
}


bool ChannelManager::exist_channel(std::string channelName) const
{
	return find_it(channelName) != channels.end();
}


// チャンネルが存在しなければ新しく作成する
// void ChannelManager::join_past(std::string channelName, Client &client)
// {
//     if (exist(channelName))
// 	{
// 		find_must_exist(channelName).join(client);
// 	}
// 	else
// 	{
// 	    channels.insert(Channel(channelName, client));
// 	}
// }

//チャンネルから離脱する
//存在しないチャンネルが指定された場合 403エラー
void ChannelManager::try_part(std::string channelName, Client& client)
{
	if (exist_channel(channelName))
	{
		get_channel(channelName).try_part(client);
	}
	else
	{
        send_errmsg(client, 403, channelName + " :No such channel");
	}
}


void ChannelManager::try_send_msg(std::string channelName, Client& client, std::string message) const
{
	if (exist_channel(channelName))
	{
		get_channel(channelName).try_send_message(client, message);
	}
	else
	{
        send_errmsg(client, 403, channelName + " :No such channel");
	}
}
