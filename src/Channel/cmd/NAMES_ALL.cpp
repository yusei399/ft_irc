#include "Client.hpp"
#include "Channel.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static void erase_exist_client(std::set<Client> &all_clients, std::set<Client> rhs)
{
	for (client_it rit = rhs.begin(); rit != rhs.end(); rit++)
	{
		if (all_clients.count(*rit))
			all_clients.erase(*rit);
	}
}

static std::string get_not_on_channel_names(const std::set<Client> &all_clients)
{
	std::string name_list = "";
	for (client_it it = all_clients.begin(); it != all_clients.end(); it++)
	{
		if (it != all_clients.begin())
			name_list += " ";
		name_list += it->get_nick();
	}
	return name_list;
}

void ChannelManager::names_all_channel(const Client &sender, const Command &cmd, std::set<Client> &all_clients)
{
	(void)cmd;
	std::set<Channel> channels = get_all_channels();
	for (channel_it it = channels.begin(); it != channels.end(); it++)
	{
		const Channel &channel = *it;
		channel.names(sender);
		erase_exist_client(all_clients, channel.get_members());
	}
}

static void names_not_on_channel(const Client &sender, const Command &cmd, std::set<Client> &all_clients)
{
	(void)cmd;
	reply(sender, RPL_NAMREPLY(sender, "*", get_not_on_channel_names(all_clients)));
	reply(sender, RPL_ENDOFNAMES(sender, "*"));
}

/// @brief 全てのチャンネルについてNAMESを行う。チャンネルに属さないクライアントはチャンネル名を*として表示する
/// @param sender
/// @param cmd
/// @param all_clients
void ChannelManager::names_all(const Client &sender, const Command &cmd, std::set<Client> all_clients)
{
	names_all_channel(sender, cmd, all_clients);
	names_not_on_channel(sender, cmd, all_clients);
}