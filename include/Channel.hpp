#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Channel
{
private:
    std::vector<Channel> channels; // IRCサーバーが持つチャンネルのリスト
    std::string name; // チャンネル名
    std::vector<std::string> users;
    // チャンネルに参加しているユーザーのリスト
    // その他、チャンネルの設定やメッセージの履歴などを保存するための変数を定義することもできる

public:
    Channel();
    ~Channel();
	
    void createChannel(std::string channelName);
    void joinChannel(std::string channelName, std::string username);
    void leaveChannel(std::string channelName, std::string username);
    void sendMessage(std::string channelName, std::string username, std::string message);
;
};
#endif

