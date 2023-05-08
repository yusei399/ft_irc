#include "ClientManager.hpp"
#include "Message.hpp"

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

std::map<int, Client>::iterator ClientManager::find_client_by_nick(const std::string & nick)
{
	for (std::map<int, Client>::iterator it = _connect.begin(); it != _connect.end(); it++)
	{
		if (it->second.get_nick() == nick)
			return it;	
	}
	return _connect.end();
}

bool ClientManager::exist_client_by_nick(const std::string &nickname)
{
	return find_client_by_nick(nickname) != _connect.end();
}

Client& ClientManager::get_client_by_nick(const std::string &nickname)
{
	assert (exist_client_by_nick(nickname));
	return const_cast<Client&>(find_client_by_nick(nickname)->second);
}

void ClientManager::privmsg(Client &sender, const std::string &reciever_name, const std::string& msg)
{
	if (exist_client_by_nick(reciever_name))
		send_msg(get_client_by_nick(reciever_name), ":" + sender.get_nick() +" PRIVMSG "+reciever_name +" :" + msg);
	else
		send_errmsg(sender, 403, reciever_name + " :No such nick");
}