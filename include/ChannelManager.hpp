#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"

typedef std::set<Channel>::iterator channel_it;

class ChannelManager
{
	std::set<Channel> channels;
public:
	channel_it find_it(std::string channelName) const;
	Channel& find_must_exist(std::string channelName) const;
	bool exist(std::string channelName) const;
    void join(std::string channelName, const Client &client);
	void try_part(std::string channelName, const Client& client);
	void try_send_msg(std::string channelName, const Client& client, std::string message) const;
};
#endif
