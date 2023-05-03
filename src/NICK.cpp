#include "../include/CommandList.hpp"
#include "../include/Client.hpp"

/*
ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED
*/
void nick(Client &client, const Command& cmd)
{
	if (cmd._params.size() == 0)
	{
		client.send_err_msg(461, ":Not enough parameters");
		return ;
	}
	if (cmd._params.size() > 1)
	{	
		client.send_err_msg(461, ":Too many parameters");
		return;
	}
	std::string new_nick = cmd._params[0];
	if (new_nick.size() > 9)
	{
		client.send_err_msg(432, ":Erroneus nickname");
		return;
	}
	client.set_nick(new_nick);
	send_message("001 :Welcome to the Internet Relay Network " + client.get_nick(), client.get_client_fd(), 0);
}
