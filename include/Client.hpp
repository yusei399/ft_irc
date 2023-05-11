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

//todo 認証まわり

//^cなどでのClientの切断に対応する
class Client
{
private:
	size_t _id; //clientはこの値で識別される
	int _fd;
	//nicknameはstatic変数で持つ
	std::string _user_name;
	std::string _real_name;
	std::string _host_name;
	std::string _server_name;
	bool authed; //パスワード認証済みかどうか
	
	void set_user_name(const std::string &user_name) {_user_name = user_name;}
	void set_real_name(const std::string &real_name) {_real_name = real_name;}
	void set_host_name(const std::string &hostname) {_host_name = hostname;}
	void set_server_name(const std::string &server_name) {_server_name = server_name;}
	
public:
	bool nickname_seted;//nicknameとuserが設定されると001メッセージが返される
	bool user_seted;
	Client();
	Client(int fd, const std::string &nc);
	~Client();
	int get_fd() const;
	bool is_authed() const{return authed;}
	size_t get_id() const{return _id;}
	std::string get_nick() const;
	std::string get_user_name() const {return _user_name;}
	std::string get_real_name() const {return _real_name;}
	std::string get_host_name() const {return _host_name;}
	std::string get_server_name() const {return _server_name;}
	void set_nick(const std::string &nick);
	void set_user_info(const std::string &user, const std::string &host, const std::string &server,const std::string &real);
	bool exist_nickname(const std::string &nick);
	void set_auth(bool b) { authed = b;}
	
	//set<client>を使う際に必要
	bool operator<(const Client& rhs) const;
	bool operator==(const Client& rhs) const;
	bool operator!=(const Client& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif