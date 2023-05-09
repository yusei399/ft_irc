#include "Channel.hpp"

#include "CheckRegister.hpp"

Channel::Channel(const std::string &name,const  Client& client, const std::string &pwd)
    :name(name), password(pwd), invited_mode(false)
{
    //todo
    //新しくチャンネルを作った時のメッセージがあってもいい
    members.insert(client);
    operators.insert(client);
}

// チャンネルから離脱する
void Channel::part(Client& target) {
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
		send_errmsg(client, 473, channel.get_name() + " :Cannot join channel (+i)");
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
    if (!correct_pass(pass))
    {
        send_errmsg(sender, 475, get_name()+ " :Cannot join channel (+k)");
        return;
    }
    members.insert(sender);
}

void Channel::broadcast(Client& sender, std::string message) const
{
    if (!require_member(sender))return;
    for (client_it reciever = members.begin(); reciever != members.end(); ++reciever)
        send_msg(*reciever, message);
}

//ユーザーがチャンネルに属していない場合442エラー
void Channel::privmsg(Client& sender, std::string message) const
{
    broadcast(sender,  ":" + sender.get_nick() +" PRIVMSG " + get_name()+ " :"+message);
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
		send_errmsg(sender, 482, get_name()+ " :You're not channel operator");
		return false;
	}
	return true;
}

//コマンドの送信者以外がチャンネルに属さないときのエラーは441なのでこの関数は使えない
bool Channel::require_member(Client& sender) const
{
    if (!is_member(sender))
	{
		send_errmsg(sender, 442, get_name() + " :You're not on that channel");
        return false;
	}
    return true;
}


static bool require_not_member(Client& sender, Client& target, Channel& channel)
{
	if (channel.is_member(target))
	{
		send_errmsg(sender, 443, target.get_nick()+ " "+channel.get_name() +" :is already on channel");
		return false;
	}
	return true;
}

void Channel::invite(Client &sender, Client& target)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_operator(sender)) return;
	if (!require_not_member(sender, target, *this)) return;
	invited.insert(target);
	send_msg(target, sender.get_nick() + " invites you to join " + get_name());
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
