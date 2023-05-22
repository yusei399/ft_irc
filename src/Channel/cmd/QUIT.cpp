#include "Client.hpp"
#include "ChannelManager.hpp"


void Channel::quit(const Client &target, const std::string &quit_msg)
{
    assert(is_member(target));
    members.erase(target);
    if (is_operator(target))
        operators.erase(target);
}

//QUIT [:msg] : msgは省略可、サーバーから抜け、全てのクライアントにメッセージを送る
void ChannelManager::quit_all_channel(Client &client, const Command& cmd)
{
	std::string msg = cmd._trailing;
	for(channel_it ch_it = channels.begin(); ch_it != channels.end(); ch_it++)
	{
		Channel &channel = const_cast<Channel&>(*ch_it);
		if (!channel.is_member(client))
			continue;
		channel.quit(client, cmd._trailing);
	}
}
