#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include <signal.h>
#include "FtCfunc.hpp"

Server::Server () : cmdManager(clientManager, channelManager, "") {}
Server::Server(int port, std::string &password) : _port(port), _password(password), cmdManager(clientManager, channelManager, password) {}
Server::~Server(){}


void Server::close_all_fd()
{
	std::vector<Client> clients = clientManager.get_connect_clients();
	for (size_t i = 0; i < clients.size(); i++)
	{
		close(clients[i].get_fd());
	}
	close(_socket_fd);
	std::cout << "close all fd" << std::endl;
}

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
	ft_bzero((char *) &reader_addr, sizeof(reader_addr));
	reader_addr.sin_family = AF_INET;
	reader_addr.sin_addr.s_addr = INADDR_ANY;
	reader_addr.sin_port = htons(_port);
	//ソケットにアドレスを結びつける
	if (bind(_socket_fd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0)
		throw std::exception();
	//コネクト要求をいくつまで待つかを設定
	if (listen(_socket_fd, SOMAXCONN) == -1)
		throw std::exception();
}

//接続
void Server::allow()
{
	std::cout << "accept ok" << std::endl;
	int connect_fd = -1;
	//一度は実行したいのでdo while
		do {
			connect_fd = accept(this->_socket_fd, NULL, NULL);
			if (connect_fd < 0)
			{
				std::cout << "connect_fd : " << connect_fd << std::endl;
				throw std::exception();
			}
			else {
				std::cout << "connection - " << connect_fd << std::endl;
				this->create_poll(connect_fd);
				clientManager.connect_client(connect_fd);
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

static std::string recieve_msg(Client &client)
{
	char buff[MSG_LEN];
	ssize_t	 byte;
	std::memset(buff, 0, sizeof(buff));
	if ((byte = recv(client.get_fd(), buff, sizeof(buff), 0)) < 0 || (byte > MSG_LEN))
	{
		if (byte < 0)
		{
			std::cout << "byte : " << byte << std::endl;
			throw std::exception();
		}
		else if (byte > MSG_LEN)
			throw std::exception();
		else
		{
			throw std::exception();
		}
	}
	std::string res = std::string(buff);
	std::cout << "recieve by " << client.get_nick()<<" : \n"<<  res<< "\n\n"<< std::endl;
	return res;
}
bool Server::has_event(size_t i, size_t event_mask)
{
	return _pfds[i].revents & event_mask;
}

void Server::poll_loop()
{
	while (1)
	{
		if (poll(_pfds.data(), _pfds.size() ,TIMEOUT)== -1)
			throw std::exception();
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents == 0)
				continue;
			Client &client = clientManager.get_client_by_fd(_pfds[i].fd);
			if (has_event(i, POLLHUP) || has_event(i, POLLERR))
				cmdManager.hangup_quit(client);
			else if (has_event(i, POLLIN))
				(_pfds[i].fd == _socket_fd) ?  this->allow() : this->recieve_cmd(client);
		}
	}
}

void Server::start()
{
	this->create_soket();
	this->create_poll(_socket_fd);
	this->poll_loop();
}


void Server::recieve_cmd(Client &sender)
{
	sender.cmd_buffer.appendBuffer(recieve_msg(sender));
	while (sender.cmd_buffer.hasComamnd())
		cmdManager.exe_cmd(sender, sender.cmd_buffer.popFrontCommand());;
}
