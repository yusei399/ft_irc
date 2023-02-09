#include "../inc/ft_irc.hpp"

int Ircserv::initSearv(int port, const std::string &password) {
	int result = 0;

	// socketの作成
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		result = -1;
		return result;
	}

	// sockaddr_inの構造体を作成し、ポート番号とアドレス情報を設定
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);

	// bindを使って、ソケットにアドレス情報を関連付け
	if (bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0)
	{
		perror("bind");
		result = -1;
		return result;
	}

	// listenを使って、接続の要求を受け付けるように設定
	if (listen(sock, 5) < 0)
	{
		perror("listen");
		result = -1;
		return result;
	}

	// 受け付ける接続のパスワードを設定
	this->_password = password;

	// 接続待ちのソケットをグローバル変数に格納
	this->_socket = sock;

	this->_port = port;

	return result;
}

