#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include "Client.hpp"
#include "ostreamExtend.hpp"
#include "Message.hpp"

typedef std::set<Client>::iterator client_it;

class Channel
{
private:
    std::string name; // チャンネル名
    std::string password; // パスワード
    std::set<Client> members;// チャンネルに参加しているユーザーのリスト 
    std::set<Client> operators;//オペレーター権限を持ったユーザーのリスト
    std::set<Client> invited; //招待されたユーザーのリスト
public:
    Channel(const std::string &name, const Client& client, const std::string &pwd);
    void part(Client& target);
    void join(Client& sender, const std::string & pass = "");
    void broadcast(Client& sender, std::string message) const;
    void privmsg(Client& sender, std::string message) const;
    bool correct_pass(const std::string& pass);
	void quit(const Client &target,  const std::string &quit_msg);
    //オペレーターコマンド
    void kick(Client &sender, Client& target, const std::string & kick_reason);
    void invite(Client &sender, Client& target);
    
    bool is_member(const Client& target) const;
    bool is_operator(const Client& target) const;
    bool require_operator(Client& sender) const;
    bool require_member(Client& sender) const;

    std::string get_name() const;
    std::string get_password() const{ return password;}
    const std::set<Client>& get_members() const;
    const std::set<Client>& get_operators() const;
    bool operator<(const Channel& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Channel& channel);

#endif

