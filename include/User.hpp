#ifndef USER_HPP
#define USER_HPP

#include "Server.hpp"

class User
{
private:
	std::string name;
	std::string nick_name;
public:
	User();
	~User();
	void user_setup();
};

#endif