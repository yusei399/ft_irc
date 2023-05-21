#include "CmdManager.hpp"


/*
 * @brief allows IRC clients and servers to negotiate new features in a backwards-compatible way
 *
 * CAP LS | CAP END
void CAP(Client &client, std::vector<struct pollfd> &pollfds, std::map<int, Client> &users, std::map<std::string, int> &nick_to_fd) {
	const std::string nick = client.getNickname();
	const int &fd = client.getFd();
#define CAP_LS ":ft_irc CAP * LS\r\n"

	if (client.getParams()[0] == "LS")
		sendMessage(fd, CAP_LS, 0);
	else if (client.getParams()[0] == "END") {
		if (client.getIsAuth() == false) {
			sendMessage(fd, ERR_PASSWDMISMATCH(nick), 0);
			sendMessage(fd, PASS_ERROR(client.getHostname()), 0);
			clearClientInfo(client, pollfds, users, nick_to_fd);
			return;
		}
		sendMessage(fd, RPL_NONE((std::string) "Authenticated ..."), 0);
		if (client.getIsNick())
		{
			client.setIsConnected(true);
			sendWelcomeMessage(client);
		}
	}
}
*/

//CAP <command> [<version>] [<parameter> …] //parameterは:から始まるtrailing
void CmdManager::cap(Client &sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 1, 3))	return;
	std::string sub_cmd = cmd._params[0];
	if (sub_cmd == "LS")
	{
		send_msg_past(sender, "CAP * LS\r\n");
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
			send_prl_none(sender, "authenticated!");
		else
			send_prl_none(sender, "fail authenticate");
	}
}