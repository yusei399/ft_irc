#include "../include/Message.hpp"

void send_msg(const Client &reciever, const std::string &message)
{
	std::string msg_lf = message + "\n";
	send(reciever.get_fd(), (msg_lf).c_str(), msg_lf.size(), 0);
}

void send_errmsg(Client &reciever, int err_code, const std::string &message)
{
	send_msg(reciever, std::to_string(err_code)+" "+ message);
}


