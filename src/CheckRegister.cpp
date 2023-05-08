#include "CheckRegister.hpp"

//パスワード認証が終わってない場合、PASS以外のコマンドは使えない
bool is_authenticated(Client &client)
{
	if (!client.is_authenticated())
	{
		send_msg(client, "you must authenticate. by PASS <password>");
		return false;
	}
	return true;
}

//NICKとUSERが設定されていない場合、他のコマンドは使えない
bool is_seted_nick_user(Client &client)
{
	if (!client.user_seted || !client.nickname_seted)
	{
		send_errmsg(client, 451, "You have not registered");
		return false;
	}
	return true;
}