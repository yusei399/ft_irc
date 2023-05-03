
#include "../include/CommandList.hpp"
#include "../include/Client.hpp"


void PONG(Client &client, std::vector<std::string> &server_name)
{
	(void)client;
	(void)server_name;
}
/*
{
	int const &fd = client.get_client_fd();
	std::string const &nick = client.get_nick();
	std::string const &server = client.get_params()[0];

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	if (client.get_params().size() > 1)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
	
	if (client.get_params().size() == 0)
	{
		std::string message = "PONG " + server_name[0] + " " + server;
		send_message(message, fd, 0);
	}
}*/