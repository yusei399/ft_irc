#include "../include/Command.hpp"

void Command::_set_cmd_type()
{
    if (_cmd_name == "CAP")
        _cmdType = CAP;
    else if (_cmd_name == "PASS")
        _cmdType = PASS;
    else if (_cmd_name == "NICK")
        _cmdType = NICK;
    else if (_cmd_name == "USER")
        _cmdType = USER;
    else if (_cmd_name == "JOIN")
        _cmdType = JOIN;
    else if (_cmd_name == "TOPIC")
        _cmdType = TOPIC;
    else if (_cmd_name == "PING")
        _cmdType = PING;
    else if (_cmd_name == "NAMES")
        _cmdType = NAMES;
    else if (_cmd_name == "MODE")
        _cmdType = MODE;
    else if (_cmd_name == "PRIVMSG")
        _cmdType = PRIVMSG;
    else if (_cmd_name == "NOTICE")
        _cmdType = NOTICE;
    else if (_cmd_name == "QUIT")
        _cmdType = QUIT;
    else if (_cmd_name == "KICK")
        _cmdType = KICK;
    else if (_cmd_name == "INVITE")
        _cmdType = INVITE;
    else if (_cmd_name == "PART")
        _cmdType = PART;
    else
        _cmdType = UNKNOWN;
}

//trailingはスペースを含むことができ、二つ目以降の:は通常の文字列として使われる
Command::Command(const std::string& cmd) : _original_string(cmd)
{
    size_t trailing_begin = cmd.find(":");
    if (trailing_begin == std::string::npos)
    {
        _has_trailing = false;
        trailing_begin = cmd.size();
    }
    else
    {
        _has_trailing = true;
    }
    std::vector<std::string> prefix_trailing = split(cmd.substr(0, trailing_begin), std::vector<std::string>(1, " "));
    _cmd_name = prefix_trailing[0];
    _params = std::vector<std::string>(prefix_trailing.begin() + 1, prefix_trailing.end());
    if (trailing_begin != cmd.size())
        _trailing = cmd.substr(trailing_begin + 1);
    _set_cmd_type();
}

void Command::debug()
{
    std::cout<<"cmd_name : " << _cmd_name<<std::endl;
    std::cout<<"params : ";
    for(size_t i = 0; i < _params.size(); i++)
    {   
        std::cout<<"<"<< _params[i]<<">, ";
    }
    std::cout<<std::endl;
    std::cout<<"trailing : " << _trailing<<std::endl;
    
}

std::string Command::get_original_str() const
{
    return _original_string;
}