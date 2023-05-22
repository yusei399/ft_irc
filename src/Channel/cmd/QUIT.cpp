#include "Client.hpp"
#include "ChannelManager.hpp"


void Channel::quit(const Command&cmd, const Client &sender, const std::string &quit_msg)
{
    assert(is_member(sender));
    members.erase(sender);
    if (is_operator(sender))
        operators.erase(sender);
	reply_cmd_all(sender, cmd);
}

//QUIT [:msg] : msgは省略可、サーバーから抜け、全てのクライアントにメッセージを送る
void ChannelManager::quit_all_channel(const Command& cmd, Client &client)
{
	std::string msg = cmd._trailing;
	for(channel_it ch_it = channels.begin(); ch_it != channels.end(); ch_it++)
	{
		Channel &channel = const_cast<Channel&>(*ch_it);
		if (!channel.is_member(client))
			continue;
		channel.quit(cmd, client, cmd._trailing);
	}
}
