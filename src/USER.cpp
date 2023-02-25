#include "../include/Command.hpp"
#include "../include/Client.hpp"

void user(Client &client)
{
	int const &fd = client.get_client_fd();

	std::string const &nick = client.get_nick();

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	std::string const &user = client.get_params()[0];
	std::string const &mode = client.get_params()[1];
	std::string const &real_name = client.get_params()[2];

	send_message("001 " + nick + " :Welcome to the Internet Relay Network " + nick, fd, 0);
	
	if (client.get_params().size() > 3)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
}