#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"


static bool is_enough_params(const Client &client, const Command& cmd)
{
	if (cmd._params.size() == 0 || cmd._params.size() > 2)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static std::vector<std::string> parse_ch_names(const Command& cmd)
{
	return split(cmd._params[0], ",");;
}

//指定されたチャンネルよりもパスワードの数が多くてもエラーは出さない(本家仕様)
//チャンネルの数に対して足りないパスワードには空文字列を入れる
static std::vector<std::string> parse_ch_pass(const Command& cmd, const std::vector<std::string> &ch_names)
{
	std::vector<std::string> ch_pwds = split(cmd._params[1], ",");
	if (ch_pwds.size() < ch_names.size())
		ch_pwds.resize(ch_names.size());
	return ch_pwds;
}

static bool is_valid_channel_name(const Client &client, const std::string & channel_name)
{
	if (channel_name == "" || channel_name[0] != '#' || channel_name == "#")
	{
        send_errmsg(client, 403, channel_name + " :No such channel");
		return false;
	}
	return true;
}

//JOIN #ch1[,#ch2] [pass_ch1,pass_ch2]
//存在しないチャンネルを指定した場合無視する(本家通り)
//複数のチャンネルを指定した際、その中で存在するチャンネルにはjoinできる
void ChannelManager::join(const Client &client, const Command& cmd)
{
	if (!is_enough_params(client, cmd)) return;
	std::vector<std::string> ch_names = parse_ch_names(cmd);
	std::vector<std::string> ch_pass = parse_ch_pass(cmd, ch_names);
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!is_valid_channel_name(client, ch_names[i]))
			continue;
		if (exist_channel(ch_names[i]))
			get_channel(ch_names[i]).join(client, ch_pass[i]);
		else
		    channels.insert(Channel(ch_names[i], client, ch_pass[i]));
		//std::cout << get_channel(ch_names[i]) << std::endl;
	}
}

//JOIN #ch1[,#ch2] [pass_ch1,pass_ch2]
//存在しないチャンネルを指定した場合無視する(本家通り)
//複数のチャンネルを指定した際、その中で存在するチャンネルにはjoinできる
/*void join(Client &client, const Command &cmd, ChannelManager &channelManager)
{
	std::vector<std::string> channelNames = parse_channels(cmd);

	if (!check_valid_cmd(client, cmd, channelManager))
		return;
	
}*/
/*
{
	int const &fd = client.get_client_fd();

	std::string const &nick = client.get_nick();

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	std::string const &pass = client.get_params()[0];

	if (pass == password)
	{
		client.set_permission(true);
		send_message("001 " + nick + " :Welcome to the Internet Relay Network " + nick, fd, 0);
	}
	else
		send_message("464 " + nick + " :Password incorrect", fd, 0);
	
	if (client.get_params().size() > 1)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
}*/