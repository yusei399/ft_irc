#include "Channel.hpp"

#include "CheckRegister.hpp"

Channel::Channel(const std::string &name,const  Client& client, const std::string &pwd)
    :name(name), password(pwd), invited_mode(false), topic_msg(""), topic_restricted(false), has_limit_(false), limit_num(0)
{
    //todo
    //新しくチャンネルを作った時のメッセージがあってもいい
    members.insert(client);
    operators.insert(client);
    reply(client, get_rpl_topic_msg(client));
    names(client);
}

int Channel::get_member_cnt()
{
    return members.size();
}

bool Channel::require_limit_safe(Client &sender)
{
    if (!has_limit())return true;
    if (limit_num < members.size() + 1)
    {
        reply(sender, ERR_CHANNELISFULL(sender, (*this)));
        return false;
    }
    return true;
}


void Channel::broadcast_reply(Client& sender, std::string message) const
{
    if (!require_sender_is_member(sender))return;
    for (client_it reciever = members.begin(); reciever != members.end(); ++reciever)
        reply(*reciever, message);
}

bool Channel::correct_pass(const std::string& pass)
{
    if (this->password == "")
        return true;
    return (this->password == pass);
}

bool Channel::is_member(const Client& target) const
{
    return members.find(target) != members.end();
}

bool Channel::is_operator(const Client& target) const
{
    return operators.find(target) != operators.end();
}

bool Channel::require_operator(Client& sender) const
{
	if (!is_operator(sender))
	{
        reply(sender, ERR_CHANOPRIVSNEEDED((*this)));
		return false;
	}
	return true;
}

//コマンドの送信者ではなく、指定したクライアントがメンバーであることを要求する
bool Channel::require_target_is_member(Client& sender, Client &target) const
{
    if (!is_member(target))
	{
        reply(sender, ERR_USERNOTINCHANNEL(sender, target, (*this)));
        return false;
	}
	return true;
}

//コマンドの送信者以外がメンバーであることを要求する
bool Channel::require_sender_is_member(const Client& sender) const
{
    if (!is_member(sender))
	{
        reply(sender, ERR_NOTONCHANNEL(sender, (*this)));
        return false;
	}
    return true;
}

std::string Channel::get_name() const
{
    return name;
}

const std::set<Client>& Channel::get_members() const
{
    return members;
}

const std::set<Client>& Channel::get_operators() const
{
    return operators;
}

//setのキーに使うために必要
bool Channel::operator<(const Channel& rhs) const
{
    return this->name < rhs.get_name();
}


std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
    os<<"--------------------"<<std::endl;
    os<<"channel_name : "<<channel.get_name()<<std::endl;
    os<<"pass         : "<<channel.get_password()<<std::endl;
    os<<"users        : \n"<<channel.get_members()<<std::endl<<std::endl;;
    os<<"operators    : \n"<<channel.get_operators()<<std::endl<<std::endl;;
    os<<"--------------------\n"<<std::endl;
    return os;
}
