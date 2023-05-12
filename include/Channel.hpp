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
    bool invited_mode;//招待されていないとJOINできないか
    std::string topic_msg;
    bool topic_restricted;//trueならオペレーターだけがトピックを変えられる
public:
    std::string get_topic();
    Channel(const std::string &name, const Client& client, const std::string &pwd);
    void part(Client& target);
    void join(Client& sender, const std::string & pass = "");
    void broadcast(Client& sender, std::string message) const;
    void privmsg(Client& sender, std::string message) const;
    void names(const Client& sender) const;
    bool correct_pass(const std::string& pass);
	void quit(const Client &target,  const std::string &quit_msg);
    //オペレーターコマンド
    void kick(Client &sender, Client& target, const std::string & kick_reason);
    void invite(Client &sender, Client& target);
    void mode_i_state(Client &client);
    void mode_i(Client &sender, bool valid);
    void mode_o(Client &sender, bool valid, Client &target);
    void mode_t_state(Client &sender);
    void mode_t(Client &sender, bool valid);
    std::string get_prl_topic_msg();
    void set_topic(Client &sender, const std::string &topic_msg);    
    void show_topic(Client &sender);
    
    bool is_member(const Client& target) const;
    bool is_operator(const Client& target) const;
    bool is_invited(const Client& target) const{return invited.find(target) != invited.end();}
    bool is_invited_mode() const{return invited_mode;}
    bool require_operator(Client& sender) const;
    bool require_sender_is_member(const Client& sender) const;
    bool require_target_is_member(Client& sender, Client &target) const;

    std::string get_name() const;
    std::string get_password() const{ return password;}
    const std::set<Client>& get_members() const;
    const std::set<Client>& get_operators() const;
    bool operator<(const Channel& rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Channel& channel);

#endif

