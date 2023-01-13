#include <iostream> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string> 
class Server
{
private:
	int port_;
	std::string	password_;
public:
	Server();
	Server(int port, std::string &password);
	~Server();
	void create_soket();
};
