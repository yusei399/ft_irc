#ifndef CHANNEL_MANAEGR_HPP
#define CHANNEL_MANAEGR_HPP

#include "Channel.hpp"
#include "Command.hpp"

typedef std::set<Channel>::iterator channel_it;

//todo
//IRCクライアントがIRCサーバーに接続する際、
//最初にNICKおよびUSERの2つのメッセージを送信して接続を登録する必要があります。
//これらのメッセージが送信されるまで、JOINやPRIVMSG
//NAMESなどの他のコマンドは使用できません。
class ChannelManager
{
	std::set<Channel> channels;
public:
	channel_it find_it(std::string channelName) const;
	Channel& get_channel(std::string channelName) const;
	std::set<Channel> get_all_channels() const;
	bool check_authenticated(Client &client);
	bool check_seted_nick_user(Client &client);
	bool exist_channel(std::string channelName) const;
	void join(Client &client, const Command& cmd);
	void nick(Client &client, const Command& cmd);
	void names(Client &client, const Command& cmd, ChannelManager &chm, std::map<int, Client> connect_clients);
	void pass(Client &client, const Command& cmd, const std::string &server_pass);
	void user(Client &client, const Command& cmd);
	void privmsg(Client &client, const Command& cmd, std::map<int, Client> &connect_clients);
	

	void try_part(std::string channelName, Client& client);
	//n
	void try_send_msg(std::string channelName, Client& client, std::string message) const;
	
};
#endif
