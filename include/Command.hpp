# ifndef COMMAND_H
# define COMMAND_H
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
#include "StringExtend.hpp"

//COMMAND [PARAMETER1] [PARAMETER2] ... [:TRAILING]
//trailingはスペースを含む
class Command{
public:
    std::string _cmd_name;
    std::vector<std::string> _params;
    std::string _trailing;  
    Command(const std::string& cmd);
    void debug();
};
#endif