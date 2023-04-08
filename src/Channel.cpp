#include "../include/Channel.hpp"

Channel::Channel() {}
Channel::~Channel() {}
Channel::Channel(const std::map<int, Client> &initial_users) : users(initial_users) {} 

void Channel::createChannel(std::string channelName) {
    Channel newChannel;
    newChannel.name = channelName;
    channels.push_back(newChannel);
}

// チャンネルに参加する関数
void Channel::joinChannel(std::string channelName, int client_fd, const Client &client) {
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
    it->users[client_fd] = client;
}

// チャンネルから離脱する関数
void Channel::leaveChannel(std::string channelName, int client_fd) {
    // チャンネルが存在するかどうかを確認する
    std::vector<Channel>::iterator it;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            // ユーザーをチャンネルから削除する
            it->users.erase(client_fd);
            break;
        }
    }
}

// チャンネルにメッセージを送信する関数
void Channel::sendMessage(std::string channelName, int client_fd, std::string message) {
    std::vector<Channel>::iterator it;
    bool found = false;
    for (it = channels.begin(); it != channels.end(); ++it) {
        if (it->name == channelName) {
            found = true;
            break;
        }
    }

    if (found) {
        auto user_it = it->users.find(client_fd);
        if (user_it != it->users.end()) {
            std::cout << "[" << it->name << "] " << user_it->second.get_nick() << ": " << message
                    << std::endl;
            for (auto &user : it->users) {
                if (user.first != client_fd) {
                    std::cout << "[Server] sending message to " << user.second.get_nick() << std::endl;
                    // send message to user
                }
            }
        } else {
            std::cout << "[Server] User with fd " << client_fd << " not found in channel " << channelName << std::endl;
        }
    } else {
        std::cout << "[Server] Channel " << channelName << " not found" << std::endl;
    }
}

