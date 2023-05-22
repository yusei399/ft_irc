#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <iostream>
#include <algorithm>
#include <unistd.h> 
#include <string> 
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <sys/socket.h>
#include "Client.hpp"


const std::string server_name = "ircserv";

#define CAP_LS ":" +server_name + " CAP * LS"
//:<prefix> <command> <parameters> :<trailing>

#define REPLY(prefix, command, parameters, trailing) ":" + (std::string)prefix + " " + (std::string)command + ((std::string)parameters == "" ? (std::string)"" : (std::string)" " + (std::string)parameters) + ((std::string)trailing == "" ? (std::string)"" : ((std::string)" :" +(std::string)trailing))

#define REP_REGIST(client, command, trailing)	REPLY(server_name, command, client.get_nick(), trailing)
#define RPL_WELCOME(client)						REP_REGIST(client, "001", "Hello! " + client.get_nick() +" Welcome to the Internet Relay Chat Network " + client.get_user_info())
#define RPL_YOURHOST(client)					REP_REGIST(client, "002", "Your host is " + server_name + ", running version 1.0")
#define RPL_CREATED(client)						REP_REGIST(client, "003", "This server was created [Thursday, June 1, 2023]")
#define RPL_MYINFO(client) 						REP_REGIST(client, "004", server_name + " 1.0 - -")

//<command>が数字のメッセージは prefixがサーバーであり、
//コマンドの通知は全てprefixがコマンドの送信者になる

//#define REP_CMD(client, cmd_name, parameters, trailing) REPLY(client.get_user_info(), cmd_name, parameters, trailing)

//INVITEは送られた人にのみINVITEの通知がいく
//送った人にはPRL_INVITING


//コマンドを使った本人にも同じ通知がいくコマンド
//JOIN、PART、PRIVMSG、QUIT
//違う返答があるコマンド
//KICK, MODE, TOPIC

#define REP_CMD(client, cmd) REPLY(client.get_user_info(), cmd.get_original_str(), "", "")

#define PONG_MSG(arg)						":" + server_name + " PONG :" + arg

//RPL
#define RPL_NONE(msg) 									REPLY(server_name, "300", "*", msg)

#define RPL_NICK_MSG(sender, command, parameters, trailing)	REPLY(server_name, command, sender.get_nick() + ((std::string)parameters == "" ? (std::string)"" : (" " + (std::string)parameters)), trailing)
#define RPL_CHANNELMODEIS(sender, ch, mode, target_nick) 			RPL_NICK_MSG(sender, "324", ch.get_name() + " " + (std::string)mode + ((std::string)target_nick == "" ? "" : " " + (std::string)target_nick), "")
#define RPL_INVITING(sender, target, ch) 				RPL_NICK_MSG(sender, "341", target.get_nick()+ " " + ch.get_name(), "")
#define RPL_NAMREPLY(sender, ch_name, name_list) 			RPL_NICK_MSG(sender, "353", ((std::string)ch_name == "*" ? "" : "= ") + ch_name ,name_list)
#define RPL_ENDOFNAMES(sender, ch_name) 						RPL_NICK_MSG(sender, "366", ch_name,"End of /NAMES list")
//									+k, -kなど
//#define RPL_CREATIONTIME(nick, channelName, nowTime) RPL_NICK_MSG(sender, "329", " #" + channelName + " " + nowTime)

//ERR
#define ERR_NOSUCHNICK(sender, target_nick) 					RPL_NICK_MSG(sender, "401", target_nick, "No such nick")
#define ERR_NOSUCHCHANNEL(sender, ch_name)					RPL_NICK_MSG(sender, "403", ch_name, "No such channel")
//#define ERR_NOTJOINCHANNEL(sender, ch)					RPL_NICK_MSG(sender, "404", ch.get_name(), "Cannot send to channel (+n)")
//#define ERR_TOOMANYCHANNELS(sender, ch)					RPL_NICK_MSG(sender, "405", ch.get_name(), "Too many channel")
#define ERR_NORECIPIENT(sender, command) 				RPL_NICK_MSG(sender, "411", "", "No recipient given (" + command + ")")
#define ERR_NOTEXTTOSEND(sender)						RPL_NICK_MSG(sender, "412", "", "No text to send")
//todo unknown
#define ERR_UNKNOWNCOMMAND(sender, cmd_name)			RPL_NICK_MSG(sender, "421", cmd_name, "Unknown command")
//#define ERR_NONICKNAMEGIVEN 							REPLY(":"+server_name, "431", "", "No nickname given")
#define ERR_ERRONEUSNICKNAME(sender)					RPL_NICK_MSG(sender, "432", "", "Error one use nickname")
#define ERR_NICKNAMEINUSE(sender, new_nick)				RPL_NICK_MSG(sender, "433", new_nick, "Nickname is already in use")
#define ERR_USERNOTINCHANNEL(sender, target, ch)		RPL_NICK_MSG(sender, "441", target.get_nick() + ch.get_name(), "They aren't on that channel")
#define ERR_NOTONCHANNEL(sender, ch)					RPL_NICK_MSG(sender, "442", ch.get_name(), "You're not on that channel")
#define ERR_USERONCHANNEL(sender, target, ch) 			RPL_NICK_MSG(sender, "443", target.get_nick()+" "+ch.get_name(), "User is already on that channel")
#define ERR_NOTREGISTERED(sender)						RPL_NICK_MSG(sender, "451", "", "You have not registered")
#define ERR_NEEDMOREPARAMS(sender, cmd_name)			RPL_NICK_MSG(sender, "461", cmd_name, "Not enough parameters")
#define ERR_ALREADYREGISTRED(sender) 					RPL_NICK_MSG(sender, "462", "", "You may not reregister")
#define ERR_PASSWDMISMATCH(sender)						RPL_NICK_MSG(sender, "464", "", "Password incorrect")
#define ERR_CHANNELISFULL(sender, ch) 					RPL_NICK_MSG(sender, "471", ch.get_name(), "Cannot join channel (+l)")
#define ERR_NOCHANMODES(sender, mode) 					RPL_NICK_MSG(sender, "472", mode, "is an unknown mode character to me")
#define ERR_INVITEONLYCHAN(sender, ch)					RPL_NICK_MSG(sender, "473", ch.get_name(), + "Cannot join channel (+i)")
#define ERR_BADCHANNELKEY(sender, ch)						RPL_NICK_MSG(sender, "475", ch.get_name(), "Cannot join channel (+k)")
//#define ERR_NOPRIVILEGES(sender)						RPL_NICK_MSG(sender, "481", "", "Permission Denied- You're not an " + sever_name +" operator")
#define ERR_CHANOPRIVSNEEDED(ch)						REPLY(":"+server_name, "482", ch.get_name(), "You're not a channel operator")

void reply(const Client &reciever, const std::string &message);

void send_welcome_msgs(const Client &reciever);
void send_rpl_none(const Client &reciever, const std::string &msg);
#endif // MESSAGE_HPP