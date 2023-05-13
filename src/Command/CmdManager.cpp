#include "CmdManager.hpp"

//cmdのパラメーターのサイズがok_size_min以上、ng_size_min未満であることを要求する
bool CmdManager::require_enough_params(Client &sender, const Command& cmd, size_t ok_size_min, size_t ng_size_min, bool require_trailing)
{
	assert(ok_size_min < ng_size_min);
	size_t param_size = cmd._params.size();
	bool ok = true;
	ok &= ok_size_min <= param_size && param_size < ng_size_min;
	if (require_trailing)
		ok &=  cmd.has_trailing();
	if (!ok)
	{
		send_numeric_msg(sender, 461, cmd.get_original_str() + " :Not enough parameters");	
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
	if 		(cmd._cmd_name == CAP) cap(sender, cmd);
	else if (cmd._cmd_name == PASS) pass(sender, cmd);
	else if (cmd._cmd_name == NICK) nick(sender, cmd);
	else if (cmd._cmd_name == USER) user(sender, cmd);
	else if (cmd._cmd_name == JOIN) join(sender, cmd);
	else if (cmd._cmd_name == TOPIC) topic(sender, cmd);
	else if (cmd._cmd_name == PING)	ping(sender, cmd);
	else if (cmd._cmd_name == NAMES) names(sender, cmd);
	else if (cmd._cmd_name == MODE) mode(sender, cmd);
	else if (cmd._cmd_name == PRIVMSG) privmsg(sender, cmd);
	else if (cmd._cmd_name == QUIT)	quit(sender, cmd);
	else if (cmd._cmd_name == KICK) kick(sender, cmd);
	else if (cmd._cmd_name == INVITE) invite(sender, cmd);
	else if (cmd._cmd_name == PART) part(sender, cmd);
	//else send_numeric_msg(sender, 421, cmd._cmd_name + " :Unknown command");
}