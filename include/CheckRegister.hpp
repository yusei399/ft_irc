#ifndef CHECKREGISTER_HPP
#define CHECKREGISTER_HPP

#include "Client.hpp"
#include "Message.hpp"

bool require_authed(Client &client);
bool require_nick_user(Client &client);

#endif // CHECKREGISTER_HPP