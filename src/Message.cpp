#include "../include/Message.hpp"

void reply(const Client &reciever, const std::string &message)
{
	std::string msg_lf = message + "\r\n";
	send(reciever.get_fd(),msg_lf.c_str(), msg_lf.size(), 0);
	std::cout << "reply to "<<reciever.get_nick()<<" {"<<msg_lf << "}\n\n"<<std::endl;
}

void send_welcome_msgs(const Client &reciever)
{
	reply(reciever, RPL_WELCOME(reciever));
	reply(reciever, RPL_YOURHOST(reciever));
	reply(reciever, RPL_CREATED(reciever));
	reply(reciever, RPL_MYINFO(reciever));
}

void send_rpl_none(const Client &reciever, const std::string &msg)
{
	reply(reciever, RPL_NONE(msg));
}
