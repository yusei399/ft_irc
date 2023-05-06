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

//クライアントの集合に対して、追加、検索、削除を行える
//todo
//全てでこれを使う

//todo Clientをすべて参照でもつ
//const&もダメかも
//
//nickNameなどが変更されたときにうまくやる
//copyを禁じれるか　＜ー諦める

//コマンドで接続が切れた時以外にも、接続が切れたらclientのリストを消す。

//本当にこれがいるのか怪しい。
//もし、insert, set, erase程度しか使わないなら
//ServerからClientManager的なものを分ける必要がないということになり
//このクラスもなくていい
class ClientStore
{
	std::map<int, Client&> _clients;
public:
	bool exist_by_nick();
	Client &find_by_nick();
	void insert(Client& client);
	void erase(Client& client);
};

#endif // CLIENT_MANAGER_HPP