#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
/*
ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED
*/
//todo使ってはいけない文字が含まれる場合
//n
void ChannelManager::nick(Client &client, const Command& cmd)
{
	if (cmd._params.size() == 0)
	{
		send_errmsg(client, 461, ":Not enough parameters");
		return ;
	}
	if (cmd._params.size() > 1)
	{
		send_errmsg(client, 461, ":Too many parameters");
		return;
	}
	std::string new_nick = cmd._params[0];
	if (new_nick.size() > 9)
	{
		send_errmsg(client, 432, ":Erroneus nickname");
		return;
	}
	client.set_nick(new_nick);
	send_msg(client, "001 :Welcome to the Internet Relay Network " + client.get_nick());
}
