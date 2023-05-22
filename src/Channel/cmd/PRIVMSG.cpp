#include "Channel.hpp"
#include "ChannelManager.hpp"

//ユーザーがチャンネルに属していない場合442エラー
void Channel::privmsg(Client& sender, std::string message) const
{
    broadcast_reply(sender,  PRIVMSG_MSG(sender, get_name(), message));
}

void ChannelManager::privmsg_to_channel(Client &sender, const std::string &channel_name, const std::string & msg)
{
	if (!require_exist_channel(sender, channel_name))
		return;
	get_channel(channel_name).privmsg(sender, msg);
}