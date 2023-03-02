#include "../include/Channel.hpp"

Channel::Channel() {}
Channel::~Channel() {}


// チャンネルを作成する関数
void Channel::createChannel(std::string channelName)
{
		Channel newChannel;
		newChannel.name = channelName;
		channels.push_back(newChannel);
}

// チャンネルに参加する関数
void Channel::joinChannel(std::string channelName, std::string username)
{
	// チャンネルが存在しなければ新しく作成する
	auto it =
			std::find_if(channels.begin(), channels.end(), [&](Channel &channel)
			{
				return channel.name == channelName;
			});
	if (it == channels.end())
	{
		createChannel(channelName);
		it = channels.end() - 1;
	}
	// ユーザーをチャンネルに追加する
	it->users.push_back(username);
}

// チャンネルから離脱する関数
void Channel::leaveChannel(std::string channelName, std::string username) {
	// チャンネルが存在するかどうかを確認する
	auto it =
			std::find_if(channels.begin(), channels.end(), [&](Channel &channel) {
				return channel.name == channelName;
			});
	if (it != channels.end())
	{
		// ユーザーをチャンネルから削除する
		auto user_it = std::find(it->users.begin(), it->users.end(), username);
		if (user_it != it->users.end())
		{
			it->users.erase(user_it);
		}
	}
}

// チャンネルにメッセージを送信する関数
void Channel::sendMessage(std::string channelName, std::string message)
{
	// チャンネルが存在するかどうかを確認する
	auto it = std::find_if(channels.begin(), channels.end(), [&](Channel &channel) {
				return channel.name == channelName;
			});
	if (it != channels.end())
	{
		// メッセージをチャンネルに送信する
		// ここで、メッセージを履歴に追加するなどの処理を行うこともできる
		for (auto user : it->users)
		{
			// ユーザーにメッセージを送信する処理を実装する
		}
	}
}

