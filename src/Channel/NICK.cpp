#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"

/*
ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED
*/
//todo使ってはいけない文字が含まれる場合
void ChannelManager::nick(Client &client, const Command& cmd)
{
	if (!check_authenticated(client)) return;
	if (cmd._params.size() == 0 || cmd._params.size() > 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return ;
	}
	std::string new_nick = cmd._params[0];
	if (new_nick.size() > 9)
	{
		send_errmsg(client, 432, ":Erroneus nickname");
		return;
	}

	if (client.exist_nickname(new_nick))
	{
		send_errmsg(client,433, new_nick + " :Nickname is already in use" );
		return;
	}
	if (!client.nickname_seted && client.user_seted)
	{
		send_msg(client, "001 :Welcome to the Internet Relay Network " + client.get_nick());
	}
	client.set_nick(new_nick);
}
