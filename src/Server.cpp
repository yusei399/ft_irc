#include "../include/Server.hpp"

Server::Server () {}
Server::Server(int port, std::string &password) : port_(port), password_(password) {}
Server::~Server(){}

void Server::create_soket()
{
	int enable = 1;
	struct sockaddr_in reader_addr;
	
	// ソケット作成、アドレスドメイン、ソケットタイプ、プロトコル
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
	{
		std::cout << "ERROR socket" << std::strerror(errno);
		exit(1);
	}

	//ソケットオプションの有効　　有効にしたい場合は０以外を設定、失敗した場合は-1が返ってくる
	if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) == -1)
	{
		std::cout << "ERROR socket option" << std::endl;
		exit(1);
	}
	//ファイルディスクリプタをノンブロッキングモードで使用する
	if (fcntl(socket_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "ERROR Fcntl" << std::endl;
		exit(1);
	}

	//通信、ポートアドレスの設定
	bzero((char *) &reader_addr, sizeof(reader_addr));
	reader_addr.sin_family = AF_INET;
	reader_addr.sin_addr.s_addr = INADDR_ANY;
	reader_addr.sin_port = htonl(port_);

	//ソケットにアドレスを結びつける
	if (bind(socket_fd, (struct sockaddr *)&reader_addr, sizeof(reader_addr)) < 0)
	{
		std::cout << "ERROR socket address" << std::endl;
		exit(1);
	}

	//コネクト要求をいくつまで待つかを設定
	if (listen(socket_fd, SOMAXCONN) == -1)
	{
		std::cout << "ERROR " << std::endl;
		exit(1);
	}
}