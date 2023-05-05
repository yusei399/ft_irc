#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"

typedef std::vector<Channel>::iterator channel_it;

class ChannelManager
{
	std::vector<Channel> channels;
public:
		
	//ChannelManager();
	void 	createChannel(std::string channelName, const Client& client);
	channel_it find_channel(std::string channelName);
	bool exist_channel(std::string channelName);
    void joinChannel(std::string channelName, const Client &client);
	
};
#endif
