#include "CmdManager.hpp"

//cmdのパラメーターのサイズがok_size_min以上、ng_size_min未満であることを要求する
bool CmdManager::require_enough_params(Client &sender, const Command& cmd, size_t ok_size_min, size_t ng_size_min, bool require_trailing)
{
	assert(ok_size_min < ng_size_min);
	size_t param_size = cmd._params.size();
	bool ok = true;
	ok &= ok_size_min <= param_size && param_size < ng_size_min;
	ok &= require_trailing && cmd._trailing != "";
	if (!ok)
	{
		send_errmsg(sender, 461, cmd.get_original_str() + " :Not enough parameters");	
		return false;
	}
	return true;
}

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