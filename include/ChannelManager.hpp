#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"
#include "Command.hpp"

typedef std::set<Channel>::iterator channel_it;

class ChannelManager
{
	std::set<Channel> channels;
public:
	channel_it find_it(std::string channelName) const;
	Channel& get_channel(std::string channelName) const;
	bool exist_channel(std::string channelName) const;
	void join(const Client &client, const Command& cmd);
	void try_part(std::string channelName, const Client& client);
	//n
	void try_send_msg(std::string channelName, const Client& client, std::string message) const;
};
#endif
