#include "CmdManager.hpp"

void CmdManager::exe_cmd(Client &sender, const Command &cmd)
{
	switch (cmd._cmdType)
	{
		case CAP:
			std::cout << "cap" << std::endl;
			break;
		case PASS:
			channelManager.pass(sender, cmd, server_pass);
			break;
		case NICK:
			channelManager.nick(sender, cmd);
			break;
		case USER:
			channelManager.user(sender, cmd);
			break;
		case JOIN:
			channelManager.join(sender, cmd);
			break;
		case TOPIC:
			std::cout << "topic" << std::endl;
			break;
		case PING:
			std::cout << "ping" << std::endl;
			break;
		case NAMES:
			names(sender, cmd);
			break;
		case MODE:
			std::cout << "mode" << std::endl;
			break;
		case PRIVMSG:
			privmsg(sender, cmd);
			break;
		case NOTICE:
			std::cout << "notice" << std::endl;
			break;
		case QUIT:
			quit(sender, cmd);
			break;
		case KICK:
			kick(sender, cmd);
			break;
		case INVITE:
			invite(sender, cmd);
			break;
		case PART:
			std::cout << "part" << std::endl;
			break;
		case UNKNOWN:
			send_errmsg(sender, 421, cmd._cmd_name + " :Unknown command");
			break;
		default:
			break;
	}
}