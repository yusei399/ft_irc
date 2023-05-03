#include "../include/Command.hpp"

//trailingはスペースを含むことができ、二つ目以降の:は通常の文字列として使われる
Command::Command(const std::string& cmd)
{
    size_t trailing_begin = cmd.find(":");
    if (trailing_begin == std::string::npos)
    {
        trailing_begin = cmd.size();
    }
    //todo区切り文字はスペースだけなのか
    std::vector<std::string> prefix_trailing = split(cmd.substr(0, trailing_begin), std::vector<std::string>(1, " "));
    _cmd_name = prefix_trailing[0];
    _params = std::vector<std::string>(prefix_trailing.begin() + 1, prefix_trailing.end());
    if (trailing_begin != cmd.size())
    {
        _trailing = cmd.substr(trailing_begin + 1);
    }
}

std::vector<Command> parse_commands(const std::string &commands_msg)
{
    std::vector<std::string> cmd_lines = split_lines(commands_msg);
    std::vector<Command> cmds;
    for(size_t i = 0; i < cmd_lines.size(); i++)
    {
        Command cmd(cmd_lines[i]);
        cmds.push_back(cmd);
    }
    return cmds;
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

/*
int main()
{
    std::vector<Command> cmds = parse_commands("JOIN #aaa bbb   ccc :msg:¥n¥r¥nCMD #bbbb ¥n¥r¥nnick ss aa s #ccc :ddd¥n¥r¥n");
    for(int i = 0; i < (int)cmds.size(); i++)
    {
        cmds[i].debug();
    }
    return 0;
}
*/
//c++ -Wall -Wextra -Werror -std=c++98 Command.cpp StringExtend.cpp