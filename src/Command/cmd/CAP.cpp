#include "CmdManager.hpp"
#include "Message.hpp"

static void cap_ls(Client &sender)
{
	reply(sender, CAP_LS);
}

static void cap_end(Client &sender)
{
	if (sender.is_authed())
		send_rpl_none(sender, "authenticated!");
	else
		send_rpl_none(sender, "fail authenticate");
}

//CAP <command> [<version>] [<parameter> …] //parameterは:から始まるtrailing
void CmdManager::cap(Client &sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 1, 3))	return;
	std::string sub_cmd = cmd._params[0];
	if (sub_cmd == "LS")
		cap_ls(sender);
	else if (sub_cmd == "END")
		cap_end(sender);
}