#include "Channel.hpp"
#include "ChannelManager.hpp"

//ユーザーがチャンネルに属していない場合442エラー
void Channel::notice(const Command &cmd, Client &sender, std::string message) const
{
	(void)message;
	reply_cmd_except_sender(sender, cmd);
}

void ChannelManager::notice_to_channel(const Command &cmd, Client &sender, const std::string &channel_name, const std::string &msg)
{
	if (!require_exist_channel(sender, channel_name))
		return;
	get_channel(channel_name).notice(cmd, sender, msg);
}