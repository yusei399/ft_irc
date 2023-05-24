#include "CmdBuffer.hpp"

static std::string trimPrefixSpace(std::string s)
{
	while(s.size() > 0 && s[0] == ' ')s.erase(s.begin());
	//while(s.size() > 0 && s.back() == ' ')s.erase(s.end()-1);
	return s;
}

static std::string trimPrefixLf(std::string s)
{
	//std::cout << "trim_prefix lf s"<<s<<"}" << std::endl;

	while(s.size())
	{
		if(s[0] == ' ' || s[0] == '\n')
			s.erase(s.begin());
		else if(s.size() > 1 && s.substr(0, 2) == "\r\n")
			s.erase(s.begin(), s.begin() + 2);
		else
			break;
	}
	//std::cout << "trim_prefix lf e" <<s<<"}" <<std::endl;
	return s;
}

/// @brief 改行コードがあることを前提とする
/// @param s 
/// @return 
std::string CmdBuffer::trimPrefix(std::string s)
{
	//std::cout << "trim_prefix {"<<s<<"}" << std::endl;
	s = trimPrefixSpace(s);
	//std::cout << "trim_spaced" << std::endl;

	if (s.size() == 0)return s;
	if (s[0] == ':')
	{
	//std::cout << "in" << std::endl;

		size_t space_pos = s.find(' ');
		if (space_pos == std::string::npos)
		{
			return "";
		}
		//std::cout << space_pos << std::endl;
		size_t command_begin = space_pos;
		while (command_begin < s.size() && s[command_begin] == ' ')
		{
			command_begin++;
		}
		//std::cout << command_begin << std::endl;
		return s.substr(command_begin);
	}
//	//std::cout << "trim_prefix ret"<<s<<"}" << std::endl;
	return s;
}

void CmdBuffer::appendBuffer(std::string s)
{
	command_buffer += s;
	////std::cout << "append_res:"<<command_buffer <<"}"<< std::endl;
	command_buffer = trimPrefixLf(command_buffer);
	////std::cout << "append_res_trim:"<<command_buffer<<"}" << std::endl;

}

bool CmdBuffer::hasComamnd()
{
	////std::cout << "has:command{"<<command_buffer <<"}"<< std::endl;
	bool ret = command_buffer.find("\n") !=std::string::npos;
	////std::cout << "has_command_res{"<<ret<<"}" << std::endl;
	return command_buffer.find("\n") !=std::string::npos;
}

/// @brief コマンドがあることが保証される
/// @return 
Command CmdBuffer::popFrontCommand()
{
	size_t cur_cmd_end;
	size_t nex_cmd_begin;
	////std::cout << "{"<<command_buffer <<"}" << std::endl;
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
	////std::cout << "cmd_str{"<<cmd_str <<"}"<< std::endl;
	//std::cout << "command_buffer{"<<command_buffer <<"}"<< std::endl;
	
	return Command(cmd_str);
}