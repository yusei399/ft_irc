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
    broadcast(sender, get_rpl_topic_msg(sender));
	//todo 違う返答がある 
}

void Channel::show_topic(Client &sender)
{
    if (!require_sender_is_member(sender)) return;
    send_msg_past(sender, get_rpl_topic_msg(sender));
}

/*
todo
送信者には、トピックが設定されたことを示すRPL_TOPICが送られます。
その他のチャンネルの人間には、トピックが変更されたことと、変更したユーザーの名前を示すTOPICが送られます。

*/