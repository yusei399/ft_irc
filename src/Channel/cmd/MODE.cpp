#include "Channel.hpp"
#include "FtCfunc.hpp"

void Channel::mode_i_state(Client &client)
{
    if (!require_sender_is_member(client))return;
    send_msg(client, "MODE " + get_name() + (invited_mode ? " +i" : " -i"));
}

void Channel::mode_i(Client &sender, bool valid)
{
    if (!require_operator(sender)) return;
    invited_mode = valid;
    broadcast(sender , "MODE "+ get_name() +" " + (valid ? "+i" : "-i") + " " + sender.get_nick());    
}

void Channel::mode_o(Client &sender, bool valid, Client &target)
{
    if (!require_operator(sender)) return;
    if (!require_sender_is_member(sender))return;
    if (!require_target_is_member(sender, target))return;
    if (valid)
    {
        operators.insert(target);
        broadcast(sender, sender.get_nick() + " sets mode +o " + target.get_nick());
    }
    else
    {
        if (operators.count(target))
            operators.erase(target);
        broadcast(sender, sender.get_nick() + " sets mode -o " + target.get_nick());    
    }
}

std::string Channel::get_topic()
{
    if (topic_msg == "")
        return "No topic is set.";
    else
        return topic_msg;
}

std::string Channel::get_channel_modeis(Client &sender, const std::string &mode, const std::string &param)
{
    std::string msg =  "324 " + get_name()+ " " + mode;
    if (param != "") msg += " " + param;
    return msg;
}

void Channel::mode_t_state(Client &sender)
{
    //tはメンバーでなくても使える
    send_msg(sender, RPL_TOPIC(sender, (*this), get_topic()));
}

void Channel::mode_t(Client &sender, bool valid)
{
    if (!require_operator(sender)) return;
    topic_restricted = valid;
    std::string mode = valid ? "mode +t" : "mode -t";
    broadcast(sender , get_channel_modeis(sender, mode, ""));
}

void Channel::mode_k_state(Client &sender)
{
    if (!require_sender_is_member(sender))return;
    std::string mode = "MODE ";
    if (password == "") mode += "-k";
    else                mode += "+k";
    send_msg(sender, get_channel_modeis(sender, mode, ""));
}

void Channel::mode_k_add(Client &sender, const std::string &new_pass)
{
    if (!require_operator(sender)) return;
    password = new_pass;
    broadcast(sender , get_channel_modeis(sender, "MODE +k", password));
}

void Channel::mode_k_rem(Client &sender)
{
    if (!require_operator(sender)) return;
    password = "";
    broadcast(sender , get_channel_modeis(sender, "MODE -k", ""));
}

//人数制限がない場合、何も出力されない仕様
void Channel::mode_l_state(Client &sender)
{
    if (!require_sender_is_member(sender))return;
    if (!has_limit())return;
    std::string mode = "MODE +l";
    send_msg(sender, get_channel_modeis(sender, mode, std::to_string(limit_num)));
}

bool Channel::require_valid_num(Client &sender, const std::string &limit_num_str)
{
    if (ft_atoi(limit_num_str, 0, 32767, allow_one_plus) == -1)
    {
        send_msg(sender, ERR_NEEDMOREPARAMS(sender, "MODE "+get_name() + " +l " + limit_num_str));
        return false;
    }
    return true;
}

void Channel::mode_l_add(Client &sender, const std::string &limit_num_str)
{
    if (!require_operator(sender)) return;
    if (!require_valid_num(sender, limit_num_str)) return;
    has_limit_ = true;
    limit_num = ft_atoi(limit_num_str, 0, 32767, allow_one_plus);
    broadcast(sender , get_channel_modeis(sender, "MODE +l", limit_num_str));
}


void Channel::mode_l_rem(Client &sender)
{
    if (!require_operator(sender)) return;
    has_limit_ = false;
    limit_num = 0;
    broadcast(sender , get_channel_modeis(sender, "MODE -l", ""));
}