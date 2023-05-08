#include "../include/Client.hpp"

static size_t generate_id()
{
	static size_t cur_id = 0;
	return cur_id++;
}

Client::Client() : authenticated(false), nickname_seted(false), user_seted(false), _id(generate_id()), _fd(-1){}

Client::Client(int fd, const std::string &nc) : _fd(fd), authenticated(false), nickname_seted(false), user_seted(false), _id(generate_id()){}

Client::~Client(){}

int Client::get_fd() const
{
	return (_fd);
}


//nicknameだけ静的変数にしている理由
// nicknameをstd::string nick_nameなどのメンバ変数で持つと
// Client a; Client b = a;
// a.nickname = "hoge";
// 等とした時にaとbでnicknameが違うという問題が起き、バグの温床になりそうだから
static std::map<Client, std::string>& get_nickname_dict()
{
	static std::map<Client, std::string> nickname_dict;
	return nickname_dict;
}

std::string Client::get_nick() const
{
	return get_nickname_dict()[*this];
}
	
void Client::set_nick(const std::string &nick)
{
	if (exist_nickname(nick))
	{
		return;
	}
	get_nickname_dict()[*this] = nick;
	nickname_seted = true;
}

bool Client::exist_nickname(const std::string &nick)
{
	std::map<Client, std::string> nicks =get_nickname_dict();
	for(std::map<Client, std::string>::iterator it = nicks.begin(); it != nicks.end(); it++)
	{
		if (it->second == nick)
			return true;
	}
	return false;
}

//Setのキーに使うために必要
bool Client::operator<(const Client& rhs) const
{
	return _id < rhs.get_id();
}

bool Client::operator==(const Client& rhs) const
{
	return _id == rhs.get_id();
}

bool Client::operator!=(const Client& rhs) const
{
	return !operator==(rhs);
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
	os<<"nick_name : " <<client.get_nick()<<", ";
	os<<"real_name : " <<client.get_real_name()<<", ";
	os<<"host_name : " <<client.get_host_name()<<", ";
	os<<"client_fd : " << client.get_fd()<<std::endl;
	return os;
}
