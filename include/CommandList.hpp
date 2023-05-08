# ifndef COMMAND_LIST_H
# define COMMAND_LIST_H
#include "Server.hpp"
#include "Message.hpp"

void join(Client &client, const Command &cmd, ChannelManager &channelManager);
void pass(Client &client, std::string const &passwprd);
void user(Client &client);
void cap(Client &client);
void quit(Client&client, const Command &cmd, ClientManager &clientManager, ChannelManager& channelManager);
void names(Client &client, const Command& cmd,  ChannelManager &chm, ClientManager& clientManager);
void PONG(Client &client, std::vector<std::string> &server_name);
void privmsg(Client &connect_client, const Command &cmd);

#endif
