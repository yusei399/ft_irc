#include "../include/Channel.hpp"

//n
Channel::Channel(const std::string &name, const Client& client)
{
    this->name = name;
    users.insert(client);
    operators.insert(client);
}

//n
// チャンネルから離脱する
// チャンネルに属していない場合442エラー
void Channel::try_part(const Client& client) {
    if (!is_user)
    {
        send_errmsg(client, 442, get_channel_name()+ " :You're not on that channel");
        return;
    }
    users.erase(client);
    if (is_operator(client))
    {
        operators.erase(client);
    }
}

void Channel::join(const Client& client)
{
    //すでに所属している場合
}

//n
//ユーザーがチャンネルに属していない場合エラーメッセージ
void Channel::try_send_message(const Client& client, std::string message) const{
    if (!is_user(client))
    {
        send_errmsg(client, 442,  get_channel_name()+ " :You're not on that channel");
    }
    else
    {
        for (client_it user = users.begin(); user != users.end(); ++user) {
            if (*user == client)continue;
            send_msg(client, "< ["+get_channel_name()+"] " + user->get_nick()+": "+message);
        }
    }
}

//n
bool Channel::is_user(const Client& client) const
{
    return users.find(client) != users.end();
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
    return users;
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
