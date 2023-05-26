#include "CmdBuffer.hpp"

static std::string trimPrefixSpace(std::string s)
{
	while (s.size() > 0 && s[0] == ' ')
		s.erase(s.begin());
	return s;
}

static std::string trimPrefixLf(std::string s)
{
	while (s.size())
	{
		if (s[0] == ' ' || s[0] == '\n')
			s.erase(s.begin());
		else if (s.size() > 1 && s.substr(0, 2) == "\r\n")
			s.erase(s.begin(), s.begin() + 2);
		else
			break;
	}
	return s;
}

/// @brief 改行コードがあることを前提とする
/// @param s
/// @return
std::string CmdBuffer::trimPrefix(std::string s)
{
	s = trimPrefixSpace(s);
	if (s.size() == 0)
		return s;
	if (s[0] == ':')
	{
		size_t space_pos = s.find(' ');
		if (space_pos == std::string::npos)
		{
			return "";
		}
		size_t command_begin = space_pos;
		while (command_begin < s.size() && s[command_begin] == ' ')
		{
			command_begin++;
		}
		return s.substr(command_begin);
	}
	return s;
}

void CmdBuffer::appendBuffer(std::string s)
{
	command_buffer += s;
	command_buffer = trimPrefixLf(command_buffer);
}

bool CmdBuffer::hasComamnd()
{
	bool ret = command_buffer.find("\n") != std::string::npos;
	return ret;
}

/// @brief コマンドがあることが保証される
/// @return
Command CmdBuffer::popFrontCommand()
{
	size_t cur_cmd_end;
	size_t nex_cmd_begin;
	if (command_buffer.find("\r\n") != std::string::npos)
	{
		cur_cmd_end = command_buffer.find("\r\n");
		nex_cmd_begin = cur_cmd_end + 2;
	}
	else if (command_buffer.find("\n") != std::string::npos)
	{
		cur_cmd_end = command_buffer.find("\n");
		nex_cmd_begin = cur_cmd_end + 1;
	}
	else
		throw std::runtime_error("cmd_buffer_error");
	std::string cmd_str = trimPrefix(command_buffer.substr(0, cur_cmd_end));
	command_buffer = trimPrefixLf(command_buffer.substr(nex_cmd_begin));
	return Command(cmd_str);
}