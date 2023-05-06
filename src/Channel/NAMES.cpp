#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"

void names(Client &client)//channel未実装
{
	(void)client;
}
/*
{
	int const &fd = client.get_client_fd();
	std::string const &nick = client.get_nick();
	std::string const &channel = client.get_params()[0];

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	if (client.get_params().size() > 1)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
	
	if (client.get_params().size() == 0)
	{
		std::string message = "353 " + nick + " = " + channel + " :";
		//for文でchannelのユーザーを取得してリスト表示
		send_message(message, fd, 0);
		send_message("366 " + nick + " " + channel + " :End of /NAMES list", fd, 0);
	}
}*/