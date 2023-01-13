#include "../include/Server.hpp"

Server::Server () {}
Server::Server(int port, std::string &password) : port_(port), password_(password) {}
Server::~Server(){}
