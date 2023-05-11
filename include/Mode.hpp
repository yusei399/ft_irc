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



#endif // MODE_HPP