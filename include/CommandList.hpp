# ifndef COMMAND_LIST_H
# define COMMAND_LIST_H
#include "Server.hpp"
#include "Message.hpp"

void pass(Client &client, std::string const &passwprd);
void nick(Client &client, const Command& cmd);
void user(Client &client);
void cap(Client &client);
void quit(Client &client);
void names(Client &client); // channel未実装
void PONG(Client &client, std::vector<std::string> &server_name);
void privmsg(Client &connect_client, const Command &cmd);

#endif
