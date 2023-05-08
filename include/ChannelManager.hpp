#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"
#include "Command.hpp"

typedef std::set<Channel>::iterator channel_it;

//Channel全体に対する操作を担う 
class ChannelManager
{
	std::set<Channel> channels;
public:
	channel_it find_it(std::string channelName) const;
	Channel& get_channel(std::string channelName) const;
	std::set<Channel> get_all_channels() const;
	bool exist_channel(std::string channelName) const;
	//const std::set<Channel> get_belong_channels(const Client &client);
	void join(Client &client, const Command& cmd);
	void nick(Client &client, const Command& cmd);
	void names_channel(Client &client, const Command& cmd,  ChannelManager &chm);
	void pass(Client &client, const Command& cmd, const std::string &server_pass);
	void user(Client &client, const Command& cmd);
	void privmsg_to_channel(Client &sender, const std::string &channel_name, const std::string & msg);
	void quit_channels(Client &client, const Command& cmd);
	void try_part(std::string channelName, Client& client);
};
#endif
