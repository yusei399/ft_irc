#include "ClientManager.hpp"

void ClientManager::connect_client(int socketfd)
{
	const std::string nick = "unknown" + std::to_string(socketfd);
	Client client(socketfd, nick);
	_connect[socketfd] = client;
}

Client& ClientManager::get_client_by_fd(int fd)
{
	return _connect[fd];
}