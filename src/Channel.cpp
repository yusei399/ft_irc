#include "../include/Channel.hpp"

//n
Channel::Channel(const std::string &name)
{
    this->name = name;
}

Channel::Channel(const std::string &name, const Client& client)
{
    this->name = name;
    members.insert(client);
    operators.insert(client);
}

//n
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

void Channel::join(const Client& client)
{
    //todo 自分がすでに属しているチャンネルにjoinを行った場合の処理がこれでいいか
    //本家はエラーをおこさないらしいので、とりあえず何もしないことにする。
    if (is_member(client))
        return;
    members.insert(client);
}

//n
//ユーザーがチャンネルに属していない場合エラーメッセージ
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

//n
bool Channel::is_member(const Client& client) const
{
    return members.find(client) != members.end();
}

//n
bool Channel::is_operator(const Client& client) const
{
    return operators.find(client) != operators.end();
}

std::string Channel::get_channel_name() const
{
    return name;
}

const std::set<Client>& Channel::get_users() const
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

//n
std::ostream& operator<<(std::ostream& os, const Channel& channel)
{
    os<<"channel_name : "<<channel.get_channel_name()<<std::endl;
    os<<"users        : "<<channel.get_users()<<std::endl;
    os<<"operators    : "<<channel.get_operators()<<std::endl;

}
