#include <iostream> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h> 
#include <string> 
#include <fcntl.h>
class Server
{
private:
	int port_;
	std::string	password_;
	int socket_fd;
public:
	Server();
	Server(int port, std::string &password);
	~Server();
	void create_soket();
};
