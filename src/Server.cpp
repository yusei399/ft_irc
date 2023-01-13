#include "../include/Server.hpp"

Server::Server () {}
Server::Server(int port, std::string &password) : port_(port), password_(password) {}
Server::~Server(){}

void Server::create_soket()
{
	// ソケット作成、アドレスドメイン、ソケットタイプ、プロトコル
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		std::cout << "ERROR socket" << std::strerror(errno);
		exit(1);
	}
}