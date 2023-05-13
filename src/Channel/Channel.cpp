#include "Channel.hpp"

#include "CheckRegister.hpp"

Channel::Channel(const std::string &name,const  Client& client, const std::string &pwd)
    :name(name), password(pwd), invited_mode(false), topic_msg(""), topic_restricted(false), has_limit_(false), limit_num(0)
{
    //todo
    //新しくチャンネルを作った時のメッセージがあってもいい
    members.insert(client);
    operators.insert(client);
    send_msg(client, get_prl_topic_msg());
    names(client);
}

// チャンネルから離脱する
void Channel::part(Client& target) {
    if (!require_sender_is_member(target))return;
    members.erase(target);  
    if (is_operator(target))
    {
        operators.erase(target);
    }
}


static bool require_invited_conditions(Client &client, Channel& channel)
{
    if (channel.is_invited_mode() && !channel.is_invited(client))
	{
		send_numeric_msg(client, 473, channel.get_name() + " :Cannot join channel (+i)");
		return false;
	}
	return true;
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
        send_numeric_msg(sender, 471,  get_name() + " :Cannot join channel (+l)");
        return false;
    }
    return true;
}

//存在しないチャンネルに対してjoinを行った場合はこの関数ではなくコンストラクタで処理する
void Channel::join(Client& sender, const std::string & pass)
{
    if (!require_invited_conditions(sender, *this)) return;
    //すでに属しているチャンネルにjoinを行った場合,本家はエラーをおこさないらしいので、とりあえず何もしないことにする。
    if (is_member(sender))
        return;
    if (!require_limit_safe(sender)) 
        return;
    if (!correct_pass(pass))
    {
        send_numeric_msg(sender, 475, get_name()+ " :Cannot join channel (+k)");
        return;
    }
    members.insert(sender);
    send_msg(sender, get_prl_topic_msg());
    names(sender);
}

void Channel::broadcast(Client& sender, std::string message) const
{
    if (!require_sender_is_member(sender))return;
    for (client_it reciever = members.begin(); reciever != members.end(); ++reciever)
        send_msg(*reciever, message);
}

//ユーザーがチャンネルに属していない場合442エラー
void Channel::privmsg(Client& sender, std::string message) const
{
    broadcast(sender,  ":" + sender.get_nick() +" PRIVMSG " + get_name()+ " :"+message);
}




static std::string get_names_str(const Channel &ch, const Client &client)
{
	std::string msg = ch.get_name() + " :";
	for(std::set<Client>::iterator cl_it = ch.get_members().begin(); cl_it != ch.get_members().end(); cl_it++)
	{
		if (cl_it != ch.get_members().begin())
			msg += " ";
		if (ch.is_operator(*cl_it))
			msg+="@";
		msg += cl_it->get_nick();
	}
	return msg;
}

void Channel::names(const Client& sender) const
{
    if (!require_sender_is_member(sender))return;
    send_msg(sender, get_names_str(*this, sender));
	send_msg(sender, get_name()+ " :End of /NAMES list");
}



void Channel::quit(const Client &target, const std::string &quit_msg)
{
    assert(is_member(target));
    members.erase(target);
    if (is_operator(target))
        operators.erase(target);
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
		send_numeric_msg(sender, 482, get_name()+ " :You're not channel operator");
		return false;
	}
	return true;
}

//コマンドの送信者ではなく、指定したクライアントがメンバーであることを要求する
bool Channel::require_target_is_member(Client& sender, Client &target) const
{
    if (!is_member(target))
	{
		send_numeric_msg(sender, 441, target.get_nick()+ " " +get_name() + " :They aren't on that channel");
        return false;
	}
	return true;
}

//コマンドの送信者以外がメンバーであることを要求する
bool Channel::require_sender_is_member(const Client& sender) const
{
    if (!is_member(sender))
	{
		send_numeric_msg(sender, 442, get_name() + " :You're not on that channel");
        return false;
	}
    return true;
}


static bool require_not_member(Client& sender, Client& target, Channel& channel)
{
	if (channel.is_member(target))
	{
		send_numeric_msg(sender, 443, target.get_nick()+ " "+channel.get_name() +" :is already on channel");
		return false;
	}
	return true;
}

void Channel::invite(Client &sender, Client& target)
{
	if (!require_operator(sender)) return;
	if (!require_not_member(sender, target, *this)) return;
	invited.insert(target);
	send_msg(target, sender.get_nick() + " invites you to join " + get_name());
}

std::string Channel::get_prl_topic_msg()
{
    std::string msg_base = get_name()+ " :" + get_topic();
    if (this->topic_msg == "")
        return  "331 " + msg_base;
    else
        return  "332 " + msg_base;
}

void Channel::set_topic(Client &sender, const std::string &topic_msg)
{
    if (topic_restricted && !require_operator(sender)) return;
    this->topic_msg = topic_msg;
    broadcast(sender,get_prl_topic_msg());
}

void Channel::show_topic(Client &sender)
{
    if (!require_sender_is_member(sender)) return;
    send_msg(sender, get_prl_topic_msg());
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
