#include "CmdManager.hpp"

void CmdManager::send_quit_msg(Client&sender, const Command &cmd)
{
	channelManager.cmd_reply_to_same_channel(sender, cmd);
}

/// @brief ctrl cなどでクライアントが抜けた場合にquitする
/// @param sender 
/// @param cmd 
void CmdManager::hangup_quit(Client&sender)
{
	send_quit_msg(sender, Command((std::string)QUIT +" : " + sender.get_nick() + " was hangup"));
	clientManager.erase_client(sender, channelManager);
}

//QUIT #a [:reason]
void CmdManager::quit(Client&client, const Command &cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd, 0, 1)) return ;
	send_quit_msg(client, cmd);
	clientManager.erase_client(client, channelManager);
}