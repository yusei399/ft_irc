#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"


static bool is_enough_params(Client &client, const Command& cmd)
{
	if (cmd._params.size() != 2)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static bool is_exist_channel(Client&client, const std::string &channel, ChannelManager& chm)
{
	if (!chm.exist_channel(channel))
	{
		send_errmsg(client, 403, channel + " :No such channel");
		return false;
	}	
	return true;
}

static bool is_exist_user(Client&client, const std::string &channel, ChannelManager& chm)
{
	if (!chm.exist_channel(channel))
	{
		send_errmsg(client, 403, channel + " :No such channel");
		return false;
	}	
	return true;
}

static bool is_exist_user(Client &client, const std::string& kick_user, ClientManager& clientManager)
{
	if (!clientManager.exist_client_by_nick(kick_user))
	{
		send_errmsg(client, 401, kick_user + " :No such nick");
		return false;
	}
	return true;
}

void kick(Client &operator_user, const Command& cmd, ClientManager& client_manager, ChannelManager& channel_manager)
{
	if (!is_authenticated(operator_user)) return;
	if (!is_seted_nick_user(operator_user)) return;
	if (!is_enough_params(operator_user, cmd))	return;
	std::string channel_name = cmd._params[0];
	std::string kick_user_name = cmd._params[1];
	if (!is_exist_channel(operator_user, channel_name, channel_manager))  return;
	if (!is_exist_user(operator_user, kick_user_name, client_manager))  return;
	Channel& channel = channel_manager.get_channel(channel_name);
	Client &ban_user = client_manager.get_client_by_nick(kick_user_name);
	std::string kick_reason = cmd._params[0];
	channel.kick(operator_user, ban_user, kick_reason);
}
