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

enum CmdType { CAP, PASS, NICK, USER, JOIN, TOPIC, PING, NAMES, MODE, PRIVMSG, NOTICE, QUIT, KICK, INVITE, PART, UNKNOWN};

//COMMAND [PARAMETER1] [PARAMETER2] ... [:TRAILING]
//trailingはスペースを含む
//コマンドの前に/をつけるかどうかによって意味が変わる場合があるらしいが、/はつけない方針でいく
class Command{
    void _set_cmd_type();
public:
    std::string _cmd_name;//存在しない値を持つことがある
    CmdType _cmdType;
    std::vector<std::string> _params;
    std::string _trailing;  
    Command(const std::string& cmd);
    void debug();
};
std::vector<Command> parse_commands(const std::string &commands_msg);

#endif