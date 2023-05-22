#include "Channel.hpp"
#include "ChannelManager.hpp"

// チャンネルから離脱する
void Channel::part(Client& target) {
    if (!require_sender_is_member(target))return;
    members.erase(target);  
    if (is_operator(target))
    {
        operators.erase(target);
    }
}

void ChannelManager::part_list(Client &sender, std::vector<std::string> &ch_names)
{
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!require_exist_channel(sender, ch_names[i]))
			continue;
		get_channel(ch_names[i]).part(sender);
	}
}