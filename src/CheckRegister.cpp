#include "CheckRegister.hpp"

//クライアントが認証されていない場合、その旨をかえす
bool is_authenticated(Client &client)
{
	if (!client.is_authenticated())
	{
		send_msg(client, "you must authenticate. by PASS <password>");
		return false;
	}
	return true;
}

//cap, pass, ping, quit以外で使う
bool is_seted_nick_user(Client &client)
{
	if (!client.user_seted || !client.nickname_seted)
	{
		send_errmsg(client, 451, "You have not registered");
		return false;
	}
	return true;
}