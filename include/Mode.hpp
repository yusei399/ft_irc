#ifndef MODE_HPP
#define MODE_HPP
#include <iostream>
#include <algorithm>
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string> 
#include <fcntl.h>
#include <signal.h>
#include <sys/poll.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Command.hpp"

const std::string MODE_I_ADD = "+i";
const std::string MODE_I_REM = "-i";
const std::string MODE_I = "i";
const std::string MODE_O_ADD = "+o";
const std::string MODE_O_REM = "-o";
const std::string MODE_T = "t";
const std::string MODE_T_ADD = "+t";
const std::string MODE_T_REM = "-t";
const std::string MODE_K = "k";
const std::string MODE_K_ADD = "+k";
const std::string MODE_K_REM = "-k";
const std::string MODE_L = "l";
const std::string MODE_L_ADD = "+l";
const std::string MODE_L_REM = "-l";

std::string get_flag(const Command&cmd)
{
	assert(cmd._params.size() > 1);
	return cmd._params[1];
}

bool is_mode_i(const Command&cmd)
{
	std::string flag = get_flag(cmd);
	return flag == MODE_I_ADD || flag == MODE_I_REM || flag == MODE_I;
}

bool is_mode_o(const Command&cmd)
{
	std::string flag = get_flag(cmd);
	return flag == MODE_O_ADD || flag == MODE_O_REM;
}

bool is_mode_t(const Command&cmd)
{
	std::string flag = get_flag(cmd);
	return flag == MODE_T_ADD || flag == MODE_T_REM || flag == MODE_T;
}

bool is_mode_k(const Command&cmd)
{
	std::string flag = get_flag(cmd);
	return flag == MODE_K_ADD || flag == MODE_K_REM || flag == MODE_K;
}

bool is_mode_l(const Command&cmd)
{
	std::string flag = get_flag(cmd);
	return flag == MODE_L_ADD || flag == MODE_L_REM || flag == MODE_L;
}



#endif // MODE_HPP