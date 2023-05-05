#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"

typedef std::set<Channel>::iterator channel_it;

class ChannelManager
{
	std::set<Channel> channels;
public:
	channel_it find_channel(std::string channelName);
	bool exist_channel(std::string channelName);
    void join(std::string channelName, const Client &client);
	void try_part(std::string channelName, const Client& client);
};
#endif
