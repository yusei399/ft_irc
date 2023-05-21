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

#define CAP_LS ":" +server_name + " CAP * LS\r\n"
//:<prefix> <command> <parameters> :<trailing>

//todo 末尾の\r\nはsend_msgの方でつける

#define REPLY(prefix, command, parameters, trailing) ":" + (std::string)prefix + " " + (std::string)command + ((std::string)parameters == "" ? (std::string)"" : (std::string)" " + (std::string)parameters) + ((std::string)trailing == "" ? (std::string)"" : ((std::string)" :" +(std::string)trailing))

#define REP_REGIST(client, command, trailing)	REPLY(server_name, command, client.get_nick(), trailing)
#define RPL_WELCOME(client)						REP_REGIST(client, "001", "Hello! " + client.get_nick() +" Welcome to the Internet Relay Chat Network " + client.get_user_info())
#define RPL_YOURHOST(client)					REP_REGIST(client, "002", "Your host is " + server_name + ", running version 1.0")
#define RPL_CREATED(client)						REP_REGIST(client, "003", "This server was created [Thursday, June 1, 2023]")
#define RPL_MYINFO(client) 						REP_REGIST(client, "004", server_name + " 1.0 - -")


#define REP_CMD(client, cmd_name, parameters, trailing) REPLY(client.get_user_info(), cmd_name, parameters, trailing)

#define JOIN_MSG(client, ch)	REP_CMD(client, "JOIN", ch.get_name(), "")

//todo ターゲットがいない場合もある      +k, -kなど
#define MODE_MSG(sender, target, ch, mode)	REP_CMD(sender, "MODE", ch.get_name() + " " + (std::string)mode + " " + target.get_nick_name())

#define QUIT_MSG(sender, msg)			    REP_CMD(sender, "QUIT :Quit", msg)
#define PRIVMSG_MSG(sender, target_name, msg)	REP_CMD(sender, "PRIVMSG", target_name, msg)
#define NOTICE_MSG(sender, msg)				REP_CMD(sender, "NOTICE",  target.get_nick(), msg)
#define INVITE_MSG(sender, msg, ch)			REP_CMD(sender, "INVITE",  target.getnick() + " " +ch.get_name())
#define KICK_MSG(sender, ch, target, msg)	REP_CMD(sender, "KICK",    ch.get_name() + " " + target.get_nick(), msg)
#define PART_MSG(sender, ch, msg) 			REP_CMD(sender, "PART", ch.get_name(), msg)
#define SETTOPIC_MSG(sender, ch, topic)		REP_CMD(sender, "TOPIC", ch.get_name(), topic)

#define NICK_MSG(oldNick, newNick)			":" + old_nick + " NICK :" + new_nick
#define PONG_MSG(arg)						":" + server_name + " PONG :" + arg

//RPL
#define RPL_NONE(msg) 									REPLY(server_name, "300", "*", msg)

#define RPL_NICK_MSG(sender, command, parameters, trailing)	REPLY(server_name, command, sender.get_nick() + ((std::string)parameters == "" ? (std::string)"" : (" " + (std::string)parameters)), trailing)
#define RPL_CHANNELMODEIS(sender, ch, mode) 			RPL_NICK_MSG(sender, "324", ch.get_name() + " " + (std::string)mode, "")
//#define RPL_INVITING(sender, target, ch) 				RPL_NICK_MSG(sender, "341", target.get_nick()+ " " + ch.get_name())
//#define RPL_NAMREPLY(sender, ch, name_list) 			RPL_NICK_MSG(sender, "353", " = " + ch.get_name(),name_list)
//#define RPL_ENDOFNAMES(sender, ch) 						RPL_NICK_MSG(sender, "366", ch.get_name(),"End of /NAMES list")
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
#define ERR_BADCHANNELKEY(sender, ch) 					RPL_NICK_MSG(sender, "457", ch.get_name(), "Cannot join channel (+k) - bad key")
#define ERR_NEEDMOREPARAMS(sender, cmd_name)			RPL_NICK_MSG(sender, "461", cmd_name, "Not enough parameters")
#define ERR_ALREADYREGISTRED(sender) 					RPL_NICK_MSG(sender, "462", "", "You may not reregister")
#define ERR_PASSWDMISMATCH(sender)						RPL_NICK_MSG(sender, "464", "", "Password incorrect")
#define ERR_CHANNELISFULL(sender, ch) 					RPL_NICK_MSG(sender, "471", ch.get_name(), "Cannot join channel (+l)")
#define ERR_NOCHANMODES(sender, mode) 					RPL_NICK_MSG(sender, "472", mode, "is an unknown mode character to me")
#define ERR_INVITEONLYCHAN(sender, ch)					RPL_NICK_MSG(sender, "473", ch.get_name(), + "Cannot join channel (+i)")
#define ERR_BADCHANNELKEY(sender, ch)						RPL_NICK_MSG(sender, "475", ch.get_name(), "Cannot join channel (+k)")
//#define ERR_NOPRIVILEGES(sender)						RPL_NICK_MSG(sender, "481", "", "Permission Denied- You're not an " + sever_name +" operator")
#define ERR_CHANOPRIVSNEEDED(ch)						REPLY(":"+server_name, "482", ch.get_name(), "You're not a channel operator")


void send_msg_past(const Client &reciever, const std::string &message);
void reply(const Client &reciever, const std::string &message);

void send_welcome_msgs(const Client &reciever);
void send_prl_none(const Client &reciever, const std::string &msg);
#endif // MESSAGE_HPP