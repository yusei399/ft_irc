#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include "Client.hpp"
#include "ostreamExtend.hpp"
#include "Message.hpp"

typedef std::set<Client>::iterator client_it;

class Channel
{
private:
    //std::vector<Channel> channels; // IRCサーバーが持つチャンネルのリスト
    std::string name; // チャンネル名
    //std::map<int, Client> users; // チャンネルに参加しているユーザーのリスト 
    std::set<Client> members;// チャンネルに参加しているユーザーのリスト 
    std::set<Client> operators;//オペレーター権限を持ったユーザーのリスト

public:
    Channel(const std::string &name);
    Channel(const std::string &name, const Client& client);

    //void createChannel(std::string channelName);
    //void joinChannel(std::string channelName, int client_fd, const Client &client);
    void try_part(const Client& client);
    void join(const Client& client);
    void try_send_message(const Client& client, std::string message) const;

    bool is_member(const Client& client) const;
    bool is_operator(const Client& client) const;

    std::string get_channel_name() const;
    const std::set<Client>& get_users() const;
    const std::set<Client>& get_operators() const;
    bool operator<(const Channel& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Channel& channel);

#endif

