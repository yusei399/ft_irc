//todo
//Clientのリストを全て持ち
//登録、削除、検索などを担う
#ifndef CLIENT_MANAGER_HPP
#define CLIENT_MANAGER_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <fcntl.h>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include "Client.hpp"

class ClientManager
{
	std::set<Client> client_list;
public:
	bool exist_by_nick();
	Client &find_by_nick();
	
};

#endif // CLIENT_MANAGER_HPP