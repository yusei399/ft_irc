#include "../include/Command.hpp"
#include "../include/Client.hpp"

void cap(Client &client)
{
	int const &fd = client.get_client_fd();

	std::string const &nick = client.get_nick();

	if (client.get_params().size() == 1)
		send_message("461 " + nick + " :Not enough parameters", fd, 0);
	
	std::string const &subcommand = client.get_params()[0];
	std::string const &subcommand_params = client.get_params()[1];

	if (subcommand == "LS")
	{
		send_message("CAP " + nick + " LS :multi-prefix sasl", fd, 0);
	}
	else if (subcommand == "REQ")
	{
		if (subcommand_params == "multi-prefix")
		{
			send_message("CAP " + nick + " ACK :multi-prefix", fd, 0);
		}
		else if (subcommand_params == "sasl")
		{
			send_message("CAP " + nick + " ACK :sasl", fd, 0);
		}
		else if (subcommand_params == "multi-prefix sasl")
		{
			send_message("CAP " + nick + " ACK :multi-prefix sasl", fd, 0);
		}
		else
		{
			send_message("CAP " + nick + " NAK :multi-prefix sasl", fd, 0);
		}
	}
	else if (subcommand == "END")
	{
		//クライアントのnickを取得 -> そのnickを使ってメッセージを送信 、user, nick, passのときと同じように表示できるようにする
		send_message("CAP " + nick + " END", fd, 0);
	}
	else
	{
		send_message("410 " + nick + " :Invalid CAP subcommand", fd, 0);
	}
	
	if (client.get_params().size() > 2)
		send_message("461 " + nick + " :Too many parameters", fd, 0);
}