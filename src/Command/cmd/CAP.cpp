#include "CmdManager.hpp"
#include "Message.hpp"

//CAP <command> [<version>] [<parameter> …] //parameterは:から始まるtrailing
void CmdManager::cap(Client &sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 1, 3))	return;
	std::string sub_cmd = cmd._params[0];
	if (sub_cmd == "LS")
	{
		reply(sender, CAP_LS);
		//send_message("CAP " + nick + " LS :multi-prefix sasl", fd, 0);
	}
	/*else if (sub_cmd == "REQ")
	{
		if (subcommand_params == "multi-prefix")
		{
			send_message("CAP " + nick + " ACK :multi-prefix", fd, 0);
		}
		else if (subcommand_params == "sasl")
		{
			send_message("CAP " + nick + " ACK :sasl", fd, 0);
		}
		else if (subcommand_params == "multi-prefix sasl")
		{
			send_message("CAP " + nick + " ACK :multi-prefix sasl", fd, 0);
		}
		else
		{
			send_message("CAP " + nick + " NAK :multi-prefix sasl", fd, 0);
		}
	}*/
	else if (sub_cmd == "END")
	{
		if (sender.is_authed())
			send_rpl_none(sender, "authenticated!");
		else
			send_rpl_none(sender, "fail authenticate");
	}
}