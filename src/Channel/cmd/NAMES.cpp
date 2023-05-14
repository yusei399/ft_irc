#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"


static std::vector<std::string> parse_channels(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

//NAMES       : 全てのクライアントを表示
//NAMES #a,#b : #a,#bチャンネルに所属するクライアントを表示
//オペレーターは名前の先頭に@がつく
void ChannelManager::names_channel(Client &client, const Command& cmd)
{
	std::vector<std::string> channels = parse_channels(cmd);
	for (size_t i = 0; i < channels.size(); i++)
	{	
		if (!require_exist_channel(client, channels[i]))
			continue;
		get_channel(channels[i]).names(client);
	}
}