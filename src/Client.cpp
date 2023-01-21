#include "../include/Client.hpp"

Client::Client(){}

Client::Client(int fd, const std::string &nc) : _fd(fd), _nick(nc){}

Client::~Client(){}


