#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <vector>
#include <string>
#include <algorithm>
#include <map>




//todo 簡単だったらクライアントのホスト名の取得を実装する
//todo nickネームなどの情報が全て揃ったらwelcomeみたいなメッセージ出す処理かく
class Client
{
private:
	int _fd;
	std::string _real_name;
	std::string _hostname;
	
public:
	Client();
	Client(int fd, const std::string &nc);
	~Client();
	int get_fd() const;
	std::string get_nick() const;
	std::string get_real_name() const;
	std::string get_host_name() const;
	void set_nick(const std::string &nick);
	void set_real_name(const std::string &real_name) {_real_name = real_name;}
	void set_hostname(const std::string &hostname) {_hostname = hostname;}
	bool exist_nickname(const std::string &nick);
	
	//set<client>を使う際に必要
	bool operator<(const Client& rhs) const;
	bool operator==(const Client& rhs) const;
	bool operator!=(const Client& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif