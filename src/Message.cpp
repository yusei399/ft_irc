#include "../include/Message.hpp"

void send_msg_past(const Client &reciever, const std::string &message)
{
	std::string msg_lf = /*":ft_irc " + */message + "\r\n";
	send(reciever.get_fd(),msg_lf.c_str(), msg_lf.size(), 0);
	std::cout << "send_msg to "<<reciever.get_nick()<<" {"<<msg_lf << "}\n\n"<<std::endl;
}

void reply(const Client &reciever, const std::string &message)
{
	std::string msg_lf = message + "\r\n";
	send(reciever.get_fd(),msg_lf.c_str(), msg_lf.size(), 0);
	std::cout << "send_msg to "<<reciever.get_nick()<<" {"<<msg_lf << "}\n\n"<<std::endl;
}

/*
void send_numeric_msg(const Client &reciever, int err_code, const std::string &message)
{
	send_msg(reciever, std::to_string(err_code)+" "+ message);
}*/

void send_welcome_msgs(const Client &reciever)
{
	reply(reciever, RPL_WELCOME(reciever));
	reply(reciever, RPL_YOURHOST(reciever));
	reply(reciever, RPL_CREATED(reciever));
	reply(reciever, RPL_MYINFO(reciever));
}

void send_prl_none(const Client &reciever, const std::string &msg)
{
	reply(reciever, RPL_NONE(msg));
}
