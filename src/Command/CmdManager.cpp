#include "CmdManager.hpp"

std::vector<Command> CmdManager::parse_commands(const std::string &commands_msg)
{
    std::vector<std::string> cmd_lines = split_lines(commands_msg);
    std::vector<Command> cmds;
    for(size_t i = 0; i < cmd_lines.size(); i++)
        cmds.push_back(Command(cmd_lines[i]));
    return cmds;
}

void CmdManager::exe_cmd(Client &sender, const Command &cmd)
{
	switch (cmd._cmdType)
	{
		case CAP:
			std::cout << "cap" << std::endl;
			break;
		case PASS:
			pass(sender, cmd);
			break;
		case NICK:
			nick(sender, cmd);
			break;
		case USER:
			user(sender, cmd);
			break;
		case JOIN:
			join(sender, cmd);
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
			mode(sender, cmd);
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