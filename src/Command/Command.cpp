#include "../include/Command.hpp"

//trailingはスペースを含むことができ、二つ目以降の:は通常の文字列として使われる
Command::Command(const std::string& cmd) : _original_string(cmd)
{
    size_t trailing_begin = cmd.find(" :");
    if (trailing_begin == std::string::npos)
    {
        _has_trailing = false;
        trailing_begin = cmd.size();
    }
    else
    {
        _has_trailing = true;
        trailing_begin = trailing_begin + 1;
    }
    std::vector<std::string> prefix_trailing = split(cmd.substr(0, trailing_begin), std::vector<std::string>(1, " "));
    _cmd_name = prefix_trailing[0];
    _params = std::vector<std::string>(prefix_trailing.begin() + 1, prefix_trailing.end());
    if (trailing_begin != cmd.size())
        _trailing = cmd.substr(trailing_begin + 1);
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