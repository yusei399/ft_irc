#include "CmdManager.hpp"

/// @brief senderと同じチャンネルに属すクライアントを返す
/// @param sender 
/// @param channelManager 
/// @return 
static std::set<Client> get_same_channel_clients(Client&sender, ChannelManager &channelManager)
{
	std::set<Client> clients;
	std::set<Channel> channels = channelManager.get_all_channels();
	for(channel_it it = channels.begin(); it != channels.end(); it++)
	{
		const Channel &channel = *it;
		if (channel.is_member(sender))
			clients.insert(channel.get_members().begin(), channel.get_members().end());
	}
	return clients;
}

static void send_quit_msg(Client&sender, const Command &cmd, const std::set<Client> &recievers)
{
	reply(sender, REP_CMD(sender, cmd));
	for (client_it it = recievers.begin(); it != recievers.end(); ++it)
	{
		Client reciever = *it;
    	if (reciever == sender)
			continue;
		reply(reciever, REP_CMD(sender, cmd));
	}
}

//QUIT #a [:reason]
void CmdManager::quit(Client&client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 1)) return ;
	send_quit_msg(client, cmd, get_same_channel_clients(client, channelManager));
	channelManager.quit_all_channel(cmd, client);
	clientManager.erase_client(client);
	close(client.get_fd());
}