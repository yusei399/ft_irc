#include "ChannelManager.hpp"

//クライアントが認証されていない場合、その旨をかえす
bool ChannelManager::check_authenticated(Client &client)
{
	if (!client.is_authenticated())
	{
		send_msg(client, "you must authenticate. by PASS <password>");
		return false;
	}
	return true;
}

//cap, pass, ping, quit以外で使う
bool ChannelManager::check_seted_nick_user(Client &client)
{
	if (!client.user_seted || !client.nickname_seted)
	{
		send_errmsg(client, 451, "You have not registered");
		return false;
	}
	return true;
}

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
		get_channel(channelName).privmsg(client, message);
	}
	else
	{
        send_errmsg(client, 403, channelName + " :No such channel");
	}
}
