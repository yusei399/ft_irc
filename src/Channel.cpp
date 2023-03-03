#include "../include/Channel.hpp"

Channel::Channel() {}
Channel::~Channel() {}


// チャンネルに参加する関数
void Channel::joinChannel(std::string channelName, std::string username)
{
    // チャンネルが存在しなければ新しく作成する
    std::vector<Channel>::iterator it;
    bool found = false;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            found = true;
            break;
        }
    }
    if (!found) {
        createChannel(channelName);
        it = channels.end() - 1;
    }
    // ユーザーをチャンネルに追加する
    it->users.push_back(username);
}

// チャンネルから離脱する関数
void Channel::leaveChannel(std::string channelName, std::string username) {
    // チャンネルが存在するかどうかを確認する
    std::vector<Channel>::iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            // ユーザーをチャンネルから削除する
            std::vector<std::string>::iterator user_it;
            for (user_it = it->users.begin(); user_it != it->users.end(); ++user_it) {
                if (*user_it == username) {
                    it->users.erase(user_it);
                    break;
                }
            }
            break;
        }
    }
}

// チャンネルにメッセージを送信する関数

void Channel::sendMessage(std::string channelName, std::string username, std::string message) {
    std::vector<Channel>::iterator it;
    bool found = false;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            found = true;
            break;
        }
    }
    if (found) {
        std::cout << "[" << it->name << "] " << username << ": " << message << std::endl;
        for (std::vector<std::string>::iterator user_it = it->users.begin(); user_it != it->users.end(); ++user_it) {
            if (*user_it != username) {
                std::cout << "[Server] sending message to " << *user_it << std::endl;
                // send message to user
            }
        }
    }
}

int main() {
    Channel channel;
    channel.joinChannel("general", "Alice");
    channel.joinChannel("general", "Bob");
    channel.sendMessage("general", "Alice", "Hello, Bob!");
    return 0;
}
