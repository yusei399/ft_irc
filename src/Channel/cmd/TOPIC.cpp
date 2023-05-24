#include "Channel.hpp"
#include "CheckRegister.hpp"

std::string Channel::get_rpl_topic_msg(const Client& sender)
{
    if (this->topic_msg == "")
        return RPL_NOTOPIC(sender, (*this));
    else
        return RPL_TOPIC(sender, (*this), this->topic_msg);
}

void Channel::set_topic(const Command& cmd, Client &sender, const std::string &topic_msg)
{
    if (topic_restricted && !require_operator(sender)) return;
    this->topic_msg = topic_msg;
    reply(sender, get_rpl_topic_msg(sender));
    reply_cmd_except_sender(sender, cmd);
}

void Channel::show_topic(Client &sender)
{
    if (!require_sender_is_member(sender)) return;
    reply(sender, get_rpl_topic_msg(sender));
}