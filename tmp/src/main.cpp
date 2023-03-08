#include "../inc/ft_irc.hpp"

int isnum(const std::string& input)
{
        for (unsigned long i = 0; i < input.length(); i++) {
                if (!isdigit(input[i])) {
                        return 1;
                }
        }
        return 0;
}

int check_num(std::string port, std::string password)
{
	if (isnum(port), isnum(password))
		return (1);
	return (0);
}

int main(int argc, char *argv[]) {
	int port;
	std::string password;
	Ircserv ircserv;

	if (argc != 3 || check_num(argv[1], argv[2]))
	{
		std::cerr << "Usage: ircserv <port> <password>" << std::endl;
		return 1;
	}

	
	port = std::stoi(argv[1]);
	password = argv[2];

	// if (ircserv.initSearv(port, password) != 0)
	{
		std::cerr << "Failed to initialize the server" << std::endl;
		return 1;
	}

	// 無限ループで受信処理を行います
/*	 while (true)
	{
		int nfds = poll(fds, nfds, -1);
		if (nfds == -1)
	{
			std::cerr << "poll failed" << std::endl;
			break;
		}

		for (int i = 0; i < nfds; i++)
	{
			if (fds[i].revents & POLLIN) {
				handleClientMessage(fds[i].fd);
			}
		}
	}
 */
	// サーバーの終了処理
	// cleanupServer();
	return 0;
}

