#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include "Client.hpp"

class Channel
{
private:
    std::vector<Channel> channels; // IRCサーバーが持つチャンネルのリスト
    std::string name; // チャンネル名
    std::map<int, Client> users; // チャンネルに参加しているユーザーのリスト 

public:
    Channel();
	Channel(const std::map<int, Client> &initial_users);
    ~Channel();

    void createChannel(std::string channelName);
    void joinChannel(std::string channelName, int client_fd, const Client &client);
    void leaveChannel(std::string channelName, int client_fd);
    void sendMessage(std::string channelName, int client_fd, std::string message);
};

#endif

