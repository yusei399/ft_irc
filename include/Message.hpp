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


//todo
#define CAP_LS ":ircserv CAP * LS\r\n"
//:<prefix> <command> <parameters> :<trailing>

//todo 末尾の\r\nはsend_msgの方でつける

#define REPLY(prefix, command, parameters, trailing) ":" + prefix + " " + command + " " + parameters + (trailing == "" ? "" : " :" +trailing)

#define REP_REGIST(client, command, trailing) REPLY(server_name, client.get_nick(), parameters, trailing)
#define RPL_WELCOME(client)		REP_REGIST(client, "001", "Hello! " + client.get_nick() +" Welcome to the Internet Relay Chat Network" + client.get_user_info())
#define RPL_YOURHOST(client)	REP_REGIST(client, "002", "Your host is " + server_name + ", running version 1.0")
#define RPL_CREATED(client)		REP_REGIST(client, "003", "This server was created [Thursday, June 1, 2023]")
#define RPL_MYINFO(client) 		REP_REGIST(client, "004", server_name + " 1.0 - -")


#define REP_CMD(client, cmd_name, parameters, trailing) REPLY(client.get_user_info(), cmd_name, parameters, trailing)

#define JOIN_MSG(client, ch)	REP_CMD(client, "JOIN", ch.get_name(), "")

//todo ターゲットがいない場合もある      +k, -kなど
#define MODE_MSG(sender, target, ch, mode)	REP_CMD(sender, "MODE", ch.get_name() + " " + mode + " " + target.get_nick_name())

#define QUIT_MSG(sender, msg)			    REP_CMD(sender, "QUIT :Quit", msg)
#define PRIVMSG_MSG(sender, target, msg)	REP_CMD(sender, "PRIVMSG", target.get_nick(), msg)
#define NOTICE_MSG(sender, msg)				REP_CMD(sender, "NOTICE",  target.get_nick(), msg)
#define INVITE_MSG(sender, msg, ch)			REP_CMD(sender, "INVITE",  target.getnick() + " " +ch.get_name())
#define KICK_MSG(sender, ch, target, msg)	REP_CMD(sender, "KICK",    ch.get_name() + " " + target.get_nick(), msg)
#define PART_MSG(sender, ch, msg) 			REP_CMD(sender, "PART", ch.get_name(), msg)
#define SETTOPIC_MSG(sender, ch, topic)		REP_CMD(sender, "TOPIC", ch.get_name(), topic)

#define NICK_MSG(oldNick, newNick)			":" + old_nick + " NICK :" + new_nick
#define PONG_MSG(arg)						":" + server_name + " PONG :" + arg

//RPL
#define PRL_MSG(command, parameters, trailing) REPLY(server_name, command, parameters, trailing)

#define RPL_NONE(msg) 					PRL_MSG("300", "*", msg)
#define RPL_NOTOPIC(sender, ch) 		PRL_MSG("331", sender.get_nick() + " TOPIC " + ch.get_name(), "No topic set for "+ ch.get_name())


void send_msg(const Client &reciever, const std::string &message);
void send_numeric_msg(const Client &reciever, int err_code, const std::string &message);

#endif // MESSAGE_HPP