#include "Message.hpp"

void send_msg(const Client &reciever, const std::string &message)
{
	send(reciever.get_fd(), message.c_str(), message.size(), 0);
}

void send_errmsg(const Client &reciever, int err_code, const std::string &message)
{
	send_msg(reciever, std::to_string(err_code)+" "+reciever.get_nick()+ " " + message);
}


