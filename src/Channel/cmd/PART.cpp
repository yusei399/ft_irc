#include "Channel.hpp"
#include "ChannelManager.hpp"

void ChannelManager::part_list(const Command& cmd, Client &sender, std::vector<std::string> &ch_names)
{
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!require_exist_channel(sender, ch_names[i]))
			continue;
		get_channel(ch_names[i]).reply_cmd_all(sender, cmd);
		get_channel(ch_names[i]).remove_client(sender);
	}
}