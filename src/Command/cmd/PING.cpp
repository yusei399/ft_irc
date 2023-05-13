#include "CmdManager.hpp"

static void pong(Client &sender, const Command &cmd)
{
	std::string msg = "PONG ";
	if (cmd._params.size() == 1)
		msg += cmd._params[0];
	else
		msg += cmd._params[0] + " " + cmd._params[1];
	send_msg(sender, msg);
}

void CmdManager::ping(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 1, 3))	return;
	pong(sender, cmd);
}
