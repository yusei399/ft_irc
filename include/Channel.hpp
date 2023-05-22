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
#include "Command.hpp"

typedef std::set<Client>::iterator client_it;
#define RPL_NOTOPIC(sender, ch) 						RPL_NICK_MSG(sender, "331", "TOPIC " + ch.get_name(), "No topic set for "+ ch.get_name())
#define RPL_TOPIC(sender, ch, topic)    				RPL_NICK_MSG(sender, "332", ch.get_name(), topic)

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
    
    bool has_limit_;// チャンネルに人数制限があるか
    size_t limit_num;

  //  std::string get_channel_modeis(Client &sender, const std::string &mode, const std::string &param);
    bool require_valid_num(Client &sender, const std::string &limit_num_str);
    bool require_limit_safe(Client &sender);
public:
    int get_member_cnt();
    bool has_limit()const {return has_limit_;}
    Channel(const Command& cmd, const std::string &name, const Client& client, const std::string &pwd);
    void remove_client(Client& target);
    void join(const Command&cmd, Client& sender, const std::string & pass = "");
    
    void broadcast(const Client& sender, std::string message) const;
    void broadcast_except_sender(const Client& sender, std::string message) const;
    void reply_cmd_all(const Client& sender, const Command& cmd) const;
    void reply_cmd_except_sender(const Client& sender, const Command& cmd) const;
    
    void privmsg(const Command&cmd, Client& sender, std::string message) const;
    void names(const Client& sender) const;
    bool correct_pass(const std::string& pass);
	void quit(const Command&cmd, const Client &sender,  const std::string &quit_msg);
    //オペレーターコマンド
    void kick(const Command&cmd, Client &sender, Client& target, const std::string & kick_reason);
    void invite(const Command&cmd, Client &sender, Client& target);
    void mode_i_state(Client &client);
    void mode_i(const Command&cmd, Client &sender, bool valid);
    void mode_o(const Command&cmd, Client &sender, bool valid, Client &target);
    void mode_t_state(Client &sender);
    void mode_t(const Command&cmd, Client &sender, bool valid);
    void mode_k_state(Client &sender);
    void mode_k_add(const Command&cmd, Client &sender, const std::string &new_pass);
    void mode_k_rem(const Command&cmd, Client &sender);
    void mode_l_state(Client &sender);
    void mode_l_add(const Command&cmd, Client &sender, const std::string &new_pass);
    void mode_l_rem(const Command&cmd, Client &sender);
    std::string get_rpl_topic_msg(const Client& sender);

    void set_topic(const Command&cmd, Client &sender, const std::string &topic_msg);    
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

