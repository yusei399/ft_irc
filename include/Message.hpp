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

void send_msg(const Client &reciever, const std::string &message);
void send_numeric_msg(const Client &reciever, int err_code, const std::string &message);

#endif // MESSAGE_HPP
