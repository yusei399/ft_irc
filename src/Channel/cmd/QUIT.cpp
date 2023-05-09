#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"

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