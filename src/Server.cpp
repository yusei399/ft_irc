#include "../include/Server.hpp"

Server::Server () {}
Server::Server(int port, std::string &password) : _port(port), _password(password) {}
Server::~Server(){}

void Server::create_soket()
{
	int enable = 1;
	struct sockaddr_in reader_addr;
	
	// ソケット作成、アドレスドメイン、ソケットタイプ、プロトコル
	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socket_fd < 0)
	{
		std::cout << "ERROR socket" << std::strerror(errno);
		exit(1);
	}

	//ソケットオプションの有効　　有効にしたい場合は０以外を設定、失敗した場合は-1が返ってくる
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
	{
		std::cout << "ERROR socket option" << std::endl;
		exit(1);
	}
	//ファイルディスクリプタをノンブロッキングモードで使用する
	if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "ERROR Fcntl" << std::endl;
		exit(1);
	}

	//通信、ポートアドレスの設定
	bzero((char *) &reader_addr, sizeof(reader_addr));
	reader_addr.sin_family = AF_INET;
	reader_addr.sin_addr.s_addr = INADDR_ANY;
	reader_addr.sin_port = htonl(_port);

	//ソケットにアドレスを結びつける
	if (bind(_socket_fd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0)
	{
		std::cout << "ERROR socket address" << std::endl;
		exit(1);
	}

	//コネクト要求をいくつまで待つかを設定
	if (listen(_socket_fd, SOMAXCONN) == -1)
	{
		std::cout << "ERROR " << std::endl;
		exit(1);
	}
	std::cout << "socket create ok" << std::endl;
}

//接続
void Server::allow()
{
	std::cout << "accept ok" << std::endl;
	int connect_fd = -1;
		do {
			connect_fd = accept(this->_socket_fd, NULL, NULL);
			if (connect_fd < 0)
			{
				std::cout << "accept ok" << std::endl;
				continue;
			}
				
			else {
				std::cout << "connection - " << connect_fd << std::endl;
				this->create_poll(connect_fd);
				connect_client(connect_fd);
			}
		} while (connect_fd == -1);
}


//poll作成
void Server::create_poll(int socket_fd)
{
	struct pollfd pollfd;
	pollfd.fd = socket_fd;
	pollfd.events = POLLIN;
	pollfd.revents = 0;
	_pfds.push_back(pollfd);
}

void Server::connect_client(int socketfd)
{
	const std::string nick = "unknown" + std::to_string(socketfd);
	Client client(socketfd, nick);
	_connect[socketfd] = client;
}


void Server::start()
{
	// this->signal_init();
	this->create_soket();
	this->create_poll(_socket_fd);
	std::cout << "server start" << std::endl;

	while (1)
	{
		std::cout << "server while " << std::endl;
		if (poll(_pfds.data(), _pfds.size() ,TIMEOUT)== -1)
		{
			std::cout << "POLL ERROR" << std::endl;
			exit(1);
		}
		std::cout << "for " << std::endl;
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			std::cout << "server in" << std::endl;
			if (_pfds[i].revents == 0)
				continue;
			if (_pfds[i].revents == POLLIN)
			{
				if (_pfds[i].fd == _socket_fd)
				{
					std::cout << "accept ok" << std::endl;
					this->allow();
				}
			}
		}
	}
}

