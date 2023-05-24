#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"
#include "Command.hpp"

typedef std::set<Channel>::iterator channel_it;

//Channel全体に対する操作を担う 
class ChannelManager
{
	std::set<Channel> channels;
	void names_all_channel(const Client &sender, const Command& cmd, std::set<Client> &all_clients);
public:
	channel_it find_it(std::string channelName) const;
	Channel& get_channel(std::string channelName) const;
	std::set<Channel> get_all_channels() const {return channels;}
	bool is_valid_channel_name(const std::string & channel_name);
	bool require_valid_channel_name(Client &client, const std::string & channel_name);
	bool require_exist_channel(Client &client, const std::string & channel_name);
	bool exist_channel(std::string channelName) const;
	//const std::set<Channel> get_belong_channels(const Client &client);
	//void join(Client &client, const Command& cmd);
	void join(const Command& cmd, Client &client, const std::vector<std::string> &ch_names, const std::vector<std::string> &ch_pass);
	//void invite(Client&sender, const std::string &target_user, const std::string &channel);
	void names_channel(Client &client, const Command& cmd);
 	void names_all(const Client &sender, const Command& cmd, std::set<Client> all_clients);
	void user(Client &client, const Command& cmd);
	void privmsg_to_channel(const Command& cmd, Client &sender, const std::string &channel_name, const std::string & msg);
	void remove_by_all_channel(Client &client);
	void part_list(const Command& cmd, Client &sender, std::vector<std::string> &ch_names);
};
#endif
