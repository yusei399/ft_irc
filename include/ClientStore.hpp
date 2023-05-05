//todo
//Clientのリストを全て持ち
//登録、削除、検索などを担う
#ifndef CLIENT_STORE_HPP
#define CLIENT_STORE_HPP

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

//クライアントの登録、検索、削除を担う
//todo
//全てでこれを使う

//todo Clientをすべて参照でもつ
//nickNameなどが変更されたときにうまくやる
//copyを禁じれるか
class ClientStore
{
	std::map<int, Client> _connect_clients;
public:
	bool exist_by_nick();
	Client &find_by_nick();
	void insert(const Client& client);
	void erase(const Client& client);
};

#endif // CLIENT_MANAGER_HPP