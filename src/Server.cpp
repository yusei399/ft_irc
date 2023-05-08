#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/CommandList.hpp"
#include <signal.h>

void privmsg(Client& client, const Command &cmd, ClientManager& clientManager, ChannelManager& channelManager);

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


/*std::map<int, Client>& Server::get_user()
{
	return (this->_user);
}*/

/*
void Server::connect_client(int socketfd)
{
	const std::string nick = "unknown" + std::to_string(socketfd);
	Client client(socketfd, nick);
	_connect[socketfd] = client;
}*/

static std::string recieve_msg(int fd)
{
	char buff[MSG_LEN];
	ssize_t	 byte;
	/*std::cout << "fd : " << fd << std::endl;
	std::cout << "buff :" << buff << std::endl;
	std::cout << "sizeof buff : " << sizeof(buff) << std::endl;
	*/
	std::memset(buff, 0, sizeof(buff));
	if ((byte = recv(fd, buff, sizeof(buff), 0)) < 0 || (byte > MSG_LEN))
	{
		if (byte < 0)
		{
			std::cout << "byte : " << byte << std::endl;
			throw std::exception();
		}
		else if (byte > MSG_LEN)
			throw std::exception();
		// else if (byte == 0)
		// quitの処理後で追記する
		//todo ?
		else
		{
			throw std::exception();
		}
	}
	return std::string(buff);
}

//todo コマンドが複数に分割されている場合
void Server::chat_in(int fd)
{
/*		std::cout << "-------------Client Message----------------" << std::endl;
		std::cout << "client fd:" << fd << std::endl;
		std::cout << "client message:" << buff << std::endl;
		std::cout << "---------------------------------------------" << std::endl;
*/
	std::vector<Command> cmds = parse_commands(recieve_msg(fd));
	for(size_t i = 0; i < cmds.size(); i++)
	{
		//std::cout << "\ncmds["<<i<<"]\n---------------------" << std::endl;cmds[i].debug();std::cout << "---------------------\n" << std::endl;
		build_in(fd, cmds[i]);
	}
	//std::cout << "message finish" << std::endl;
}

void Server::start()
{
	this->create_soket();
	this->create_poll(_socket_fd);

	while (1)
	{
		if (poll(_pfds.data(), _pfds.size() ,TIMEOUT)== -1)
			throw std::exception();
		for (size_t i = 0; i < _pfds.size(); i++)
		{
			if (_pfds[i].revents == 0)
				continue;
			if (_pfds[i].revents == POLLIN)
				(_pfds[i].fd == _socket_fd) ?  this->allow() : this->chat_in(_pfds[i].fd);
		}
	}
}

void Server::build_in(int fd, const Command &cmd)
{
	Client &client = clientManager.get_client_by_fd(fd);
	CmdType cmdType = cmd._cmdType;

	switch (cmdType)
	{
		case CAP:
			std::cout << "cap" << std::endl;
			break;
		case PASS:
			channelManager.pass(client, cmd, _password);
			break;
		case NICK:
			channelManager.nick(client, cmd);
			break;
		case USER:
			channelManager.user(client, cmd);
			break;
		case JOIN:
			channelManager.join(client, cmd);
			break;
		case TOPIC:
			std::cout << "topic" << std::endl;
			break;
		case PING:
			std::cout << "ping" << std::endl;
			break;
		case NAMES:
			channelManager.names(client, cmd, channelManager, clientManager._connect);
			break;
		case MODE:
			std::cout << "mode" << std::endl;
			break;
		case PRIVMSG:
			privmsg(client, cmd, clientManager, channelManager);
			break;
		case NOTICE:
			std::cout << "notice" << std::endl;
			break;
		case QUIT:
			std::cout << "quit" << std::endl;
			break;
		case KICK:
			std::cout << "kick" << std::endl;
			break;
		case INVITE:
			std::cout << "invite" << std::endl;
			break;
		case PART:
			std::cout << "part" << std::endl;
			break;
		//ok
		case UNKNOWN:
			send_errmsg(client, 421, cmd._cmd_name + " :Unknown command");
			break;
		default:
			break;
	}
}
