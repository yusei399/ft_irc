# ifndef COMMAND_H
# define COMMAND_H
#include "Server.hpp"

void pass(Client &client, std::string const &passwprd);
void nick(Client &client);
void user(Client &client);
void cap(Client &client);
void quit(Client &client);
void names(Client &client); // channel未実装

#endif
