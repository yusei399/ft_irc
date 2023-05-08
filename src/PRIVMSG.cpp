#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"

static bool is_valid_param(const Client &client, const Command &cmd)
{
	bool is_ok = true;
	if (cmd._params.size() == 0)
	{
		send_errmsg(client, 411, ":No recipient given (" + cmd.get_original_str()+ ")");
		is_ok = false;
	}
	else if (cmd._params.size() > 1)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		is_ok = false;
	}
	if (cmd._trailing == "")
	{
		send_errmsg(client, 412, ":No text to send");
		is_ok = false;	
	}
	return is_ok;
}



static std::vector<std::string> parse_recievers(const Command&cmd)
{
	return split(cmd._params[0], ",");
}

static bool is_channel(const std::string &reicieve)
{
	return reicieve != "" && reicieve[0] == '#';
}

void privmsg(Client& client, const Command &cmd, ClientManager& clientManager, ChannelManager& channelManager)
{
	if (!is_authenticated(client)) return;
	if (!is_seted_nick_user(client)) return;
	if (!is_valid_param(client, cmd)) return;
	std::vector<std::string> recievers = parse_recievers(cmd);
	for (size_t i = 0; i < recievers.size(); i++)
	{
		if (is_channel(recievers[i]))
			channelManager.privmsg_to_channel(client, recievers[i], cmd._trailing);
		else
			clientManager.privmsg(client, recievers[i], cmd._trailing);
	}
}