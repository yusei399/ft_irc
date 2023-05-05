#include "../include/ChannelManager.hpp"

ChannelManager::ChannelManager() {}


//n
void 	ChannelManager::createChannel(std::string channelName, const Client& client)
{
	if (exist_channel(channelName))
		return;
    channels.push_back(Channel(channelName, client));
}

//見つからなかったらchannels.end()を返す
channel_it ChannelManager::find_channel(std::string channelName)
{
    for (channel_it it = channels.begin(); it != channels.end(); ++it) {
        if (it->get_channel_name() == channelName) {
            return it;
        }
    }
	return channels.end();
}

bool ChannelManager::exist_channel(std::string channelName)
{
	return find_channel(channelName) != channels.end();
}

// チャンネルが存在しなければ新しく作成する
void ChannelManager::joinChannel(std::string channelName, const Client &client)
{
    if (exist_channel(channelName))
	{

	}
	else
	{
		createChannel(channelName, client);

	}
	
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
        it = channels.end();
        --it;
    }
    // ユーザーをチャンネルに追加する
    it->users.insert(std::pair<int, Client>(client_fd, client));
}