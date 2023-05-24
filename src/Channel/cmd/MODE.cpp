#include "Channel.hpp"
#include "FtCfunc.hpp"

void Channel::mode_i_state(Client &client)
{
    if (!require_sender_is_member(client))return;
    reply(client ,RPL_CHANNELMODEIS(client, (*this), (invited_mode ? "+i" : "-i"), ""));
}

void Channel::mode_i(const Command&cmd, Client &sender, bool valid)
{
    if (!require_operator(sender)) return;
    invited_mode = valid;
    reply_cmd_all(sender, cmd);
}

void Channel::mode_o(const Command&cmd, Client &sender, bool valid, Client &target)
{
    if (!require_operator(sender)) return;
    if (!require_sender_is_member(sender))return;
    if (!require_target_is_member(sender, target))return;
    reply_cmd_all(sender, cmd);
    if (valid)
    {
        operators.insert(target);
    }
    else
    {
        if (operators.count(target))
            operators.erase(target);    
    }
}

void Channel::mode_t_state(Client &sender)
{
    //tはメンバーでなくても使える
    reply(sender, get_rpl_topic_msg(sender));
}

void Channel::mode_t(const Command&cmd, Client &sender, bool valid)
{
    if (!require_operator(sender)) return;
    topic_restricted = valid;
    reply_cmd_all(sender, cmd);
}

void Channel::mode_k_state(Client &sender)
{
    if (!require_sender_is_member(sender))return;
    std::string mode;
    if (password == "") mode = "-k";
    else                mode = "+k";
    reply(sender , RPL_CHANNELMODEIS(sender, (*this), mode, ""));
}

void Channel::mode_k_add(const Command&cmd, Client &sender, const std::string &new_pass)
{
    if (!require_operator(sender)) return;
    password = new_pass;
    reply_cmd_all(sender, cmd);
}

void Channel::mode_k_rem(const Command&cmd, Client &sender)
{
    if (!require_operator(sender)) return;
    password = "";
    reply_cmd_all(sender, cmd);
}

/// @brief 人数制限がない場合、何も出力されない仕様
/// @param sender 
void Channel::mode_l_state(Client &sender)
{
    if (!require_sender_is_member(sender))return;
    if (!has_limit())return;
    reply(sender , RPL_CHANNELMODEIS(sender, (*this), "+l", std::to_string(limit_num)));
}

bool Channel::require_valid_num(Client &sender, const std::string &limit_num_str)
{
    if (ft_atoi(limit_num_str, 0, 32767, allow_one_plus) == -1)
    {
        reply(sender, ERR_NEEDMOREPARAMS(sender, "MODE "+get_name() + " +l " + limit_num_str));
        return false;
    }
    return true;
}

void Channel::mode_l_add(const Command&cmd, Client &sender, const std::string &limit_num_str)
{
    if (!require_operator(sender)) return;
    if (!require_valid_num(sender, limit_num_str)) return;
    has_limit_ = true;
    limit_num = ft_atoi(limit_num_str, 0, 32767, allow_one_plus);
    reply_cmd_all(sender, cmd);
}


void Channel::mode_l_rem(const Command&cmd, Client &sender)
{
    if (!require_operator(sender)) return;
    has_limit_ = false;
    limit_num = 0;
    reply_cmd_all(sender, cmd);
}