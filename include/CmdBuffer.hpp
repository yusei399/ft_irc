# ifndef COMMAND_BUFFER_H
# define COMMAND_BUFFER_H
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
#include <stdexcept>
#include "Command.hpp"

class CmdBuffer
{
	std::string command_buffer;
	std::string trimPrefix(std::string s);
public:
	void appendBuffer(std::string s);
	bool hasComamnd();
	Command popFrontCommand();
};
#endif