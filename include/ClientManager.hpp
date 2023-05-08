#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "Client.hpp"

class ClientManager
{
public:
	std::map<int, Client> _connect;
	void connect_client(int socketfd);
	Client& get_client_by_fd(int fd);
};


#endif // CLIENTMANAGER_HPP