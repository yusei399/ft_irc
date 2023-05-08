#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
/*
static bool valid_arg_cnt(Client &connect_client, Command &cmd)
{
	if (cmd._params.size() != 1)
}*/

void privmsg(Client &connect_client, const Command &cmd)
{
	//if (!check_authenticated(client)) return;
	//check_seted_nick_user
	//
	//if (!valid_arg_cnt(connect_client, cmd)) return;
	(void)connect_client;
	(void)cmd;
}