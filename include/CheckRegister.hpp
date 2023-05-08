#ifndef CHECKREGISTER_HPP
#define CHECKREGISTER_HPP

#include "Client.hpp"
#include "Message.hpp"

bool is_authenticated(Client &client);
bool is_seted_nick_user(Client &client);

#endif // CHECKREGISTER_HPP