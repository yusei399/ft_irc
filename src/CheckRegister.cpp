#include "CheckRegister.hpp"

//パスワード認証が終わってない場合、PASS以外のコマンドは使えない
bool require_authed(Client &client)
{
	if (!client.is_authed())
	{
		reply(client, RPL_NONE("you must authenticate. by PASS <password>"));
		return false;
	}
	return true;
}

//NICKとUSERが設定されていない場合、他のコマンドは使えない
bool require_nick_user(Client &client)
{
	if (!client.user_seted || !client.nickname_seted)
	{
		reply(client, ERR_NOTREGISTERED(client));
		return false;
	}
	return true;
}