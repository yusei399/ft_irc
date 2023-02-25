#include "../include/Command.hpp"
#include "../include/Client.hpp"

void nick(Client &client)
{
	int const &fd = client.get_client_fd();

	std::string const &nick = client.get_nick();

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	std::string const &new_nick = client.get_params()[0];

	if (new_nick.size() > 9)
		send_message("432 " + nick + " :Erroneus nickname", fd, 0);
	else
	{
		client.set_nick(new_nick);
		send_message("001 " + nick + " :Welcome to the Internet Relay Network " + nick, fd, 0);
	}
	
	if (client.get_params().size() > 1)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
}