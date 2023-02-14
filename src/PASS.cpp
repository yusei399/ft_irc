#include "../include/Command.hpp"
#include "../include/Client.hpp"

void pass(Client &client, std::string const &password)
{
	int const &fd = client.get_client_fd();

	std::string const &nick = client.get_nick();

	if (client.get_params().size() == 1)
	{
		send_message(
	}
}