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

void CmdManager::send_quit_msg(Client&sender, const Command &cmd)
{
	const std::set<Client> &recievers = get_same_channel_clients(sender, channelManager);
	//reply(sender, REP_CMD(sender, cmd));
	for (client_it it = recievers.begin(); it != recievers.end(); ++it)
	{
		Client reciever = *it;
    	if (reciever == sender)
			continue;
		reply(reciever, REP_CMD(sender, cmd));
	}
}

/// @brief ctrl cなどでクライアントが抜けた場合にquitする
/// @param sender 
/// @param cmd 
void CmdManager::hangup_quit(Client&sender)
{
	send_quit_msg(sender, Command((std::string)QUIT +" : " + sender.get_nick() + " was hangup"));
	clientManager.erase_client(sender, channelManager);
}

//QUIT #a [:reason]
void CmdManager::quit(Client&client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 1)) return ;
	send_quit_msg(client, cmd);
	clientManager.erase_client(client, channelManager);
}