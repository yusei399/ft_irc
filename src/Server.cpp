#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include <signal.h>

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
		throw std::exception();
	//ソケットオプションの有効　　有効にしたい場合は０以外を設定、失敗した場合は-1が返ってくる
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
		throw std::exception();
	//ファイルディスクリプタをノンブロッキングモードで使用する
	if (fcntl(_socket_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::exception();
	//通信、ポートアドレスの設定
	bzero((char *) &reader_addr, sizeof(reader_addr));
	reader_addr.sin_family = AF_INET;
	reader_addr.sin_addr.s_addr = INADDR_ANY;
	reader_addr.sin_port = htons(_port);
	//ソケットにアドレスを結びつける
	if (bind(_socket_fd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0)
		throw std::exception();
	//コネクト要求をいくつまで待つかを設定
	if (listen(_socket_fd, SOMAXCONN) == -1)
		throw std::exception();
	std::cout << "socket create ok, fd = " << _socket_fd << std::endl;
}

//接続
void Server::allow()
{
	std::cout << "accept ok" << std::endl;
	int connect_fd = -1;
		do {
			connect_fd = accept(this->_socket_fd, NULL, NULL);
			if (connect_fd < 0)
				throw std::exception();
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


std::map<int, Client>& Server::get_user()
{
	return (this->_user);
}

int Server::search(const std::string &str, const std::string &target)
{
	for (size_t i = 0; i < str.size(); i++)
	{
		size_t j = 0;
		if (str[i] == target[0])
		{
			while (str[i] && target[j] && str[i] == target[j])
				i++, j++;
			if (j == target.size())
				return i - (target.size() - 1);
		}
	}
	return -1;
}

void Server::connect_client(int socketfd)
{
	const std::string nick = "unknown" + std::to_string(socketfd);
	Client client(socketfd, nick);
	_connect[socketfd] = client;
}

void Server::chat_in(int fd)
{
	char buff[MSG_LEN];
	int	 byte;

	std::memset(buff, 0, sizeof buff);
	if ((byte = recv(_socket_fd, buff, sizeof buff, 0)) <= 0 || (byte > MSG_LEN))
	{
		if (byte < 0)
			throw std::exception();
		else if (byte > MSG_LEN)
			throw std::exception();
		// else if (byte == 0)
		// quitの処理後で追記する
		Client &client = _connect[fd];
		std::cout << "-------------Client Message----------------" << std::endl;
		std::cout << "client fd:" << fd << std::endl;
		std::cout << "client message:" << buff << std::endl;
		std::cout << "---------------------------------------------" << std::endl;

		size_t i = 0;
		while (search(&buff[i], "\r\n") != -1)
		{
			size_t len = 0;
			std::string command;
			while (buff[i] != '\r' && buff[i] != '\n')
				i++, len++;
			command.append(&buff[i - len], len + 2);
			client.command_parser(command);
		}
	}
}

void Server::start()
{
	this->create_soket();
	this->create_poll(_socket_fd);

	while (1)
	{
		std::cout << "pfds size = " << _pfds.size() << std::endl;
		std::cout << "pfds.begin() = " << _pfds.data()->fd << std::endl;
		if (poll(_pfds.data(), _pfds.size() ,TIMEOUT)== -1)
			throw std::exception();
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents == 0)
				continue;
			if (_pfds[i].revents == POLLIN)
			{
				if (_pfds[i].fd == _socket_fd)
				{
					std::cout << "accept ok" << std::endl;
					this->allow();
				}
				else
				{
					this->chat_in(_socket_fd);
				}
			}
		}
	}
}
