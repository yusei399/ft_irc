#include "../include/Command.hpp"
#include "../include/Client.hpp"

void pass(Client &client, std::string const &password)
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
}