#include "Channel.hpp"


Channel::Channel(const std::string &name, const Client& client, const std::string &pwd)
    :name(name), password(pwd)
{
    members.insert(client);
    operators.insert(client);
}

// チャンネルから離脱する
// チャンネルに属していない場合442エラー
void Channel::try_part(const Client& client) {
    if (!is_member(client))
    {
        send_errmsg(client, 442, get_channel_name() + " :You're not on that channel");
        return;
    }
    members.erase(client);
    if (is_operator(client))
    {
        operators.erase(client);
    }
}

//存在しないチャンネルに対してjoinを行った場合はこの関数ではなくコンストラクタで処理する
void Channel::join(const Client& client, const std::string & pass)
{
    //すでに属しているチャンネルにjoinを行った場合,本家はエラーをおこさないらしいので、とりあえず何もしないことにする。
    if (is_member(client))
        return;
    if (!correct_pass(pass))
    {
        send_errmsg(client, 475, get_channel_name()+ " :Cannot join channel (+k)");
        return;
    }
    members.insert(client);
}

//n
//ユーザーがチャンネルに属していない場合442エラー
void Channel::try_send_message(const Client& client, std::string message) const{
    if (!is_member(client))
    {
        send_errmsg(client, 442,  get_channel_name()+ " :You're not on that channel");
    }
    else
    {
        for (client_it user = members.begin(); user != members.end(); ++user) {
            if (*user == client)continue;
            send_msg(client, "< ["+get_channel_name()+"] " + user->get_nick()+": "+message);
        }
    }
}

bool Channel::correct_pass(const std::string& pass) const
{
    if (this->password == "")
        return true;
    return (this->password == pass);
}

bool Channel::is_member(const Client& client) const
{
    return members.find(client) != members.end();
}

bool Channel::is_operator(const Client& client) const
{
    return operators.find(client) != operators.end();
}

std::string Channel::get_channel_name() const
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
    return this->name < rhs.get_channel_name();
}


std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
    os<<"--------------------"<<std::endl;
    os<<"channel_name : "<<channel.get_channel_name()<<std::endl;
    os<<"pass         : "<<channel.get_password()<<std::endl;
    os<<"users        : \n"<<channel.get_members()<<std::endl<<std::endl;;
    os<<"operators    : \n"<<channel.get_operators()<<std::endl<<std::endl;;
    os<<"--------------------\n"<<std::endl;
    return os;
}
