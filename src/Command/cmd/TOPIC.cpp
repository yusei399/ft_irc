#include "CmdManager.hpp"


/*
チャンネルのトピックとは、チャンネルの内容や目的を表す短い文です。チャンネルに参加すると、トピックが表示されます。また、チャンネルのリストを見るときにも、トピックが表示されます。トピックは、チャンネルのオペレーターが変更できます。

TOPICコマンドは、チャンネルのトピックを設定したり、確認したりするために使います。TOPICコマンドのパラメーターの渡し方は、次のようになります。

TOPIC <channel> [<topic>]

<channel>: トピックを設定したり、確認したりするチャンネルの名前です。
<topic>: トピックを設定する場合に指定します。省略すると、現在のトピックを確認できます。

生じうるエラーは、次のとおりです。

ERR_NEEDMOREPARAMS (461): パラメーターが足りない場合に発生します。例えば、次のように実行した場合です。
TOPIC

ERR_NOSUCHCHANNEL (403): 存在しないチャンネルを指定した場合に発生します。例えば、次のように実行した場合です。
TOPIC #bar

ERR_NOTONCHANNEL (442): 指定したチャンネルに参加していない場合に発生します。例えば、#fooチャンネルに参加していないnick1が、次のように実行した場合です。
TOPIC #foo

ERR_CHANOPRIVSNEEDED (482): オペレーター権限がないユーザーがトピックを設定しようとした場合に発生します。例えば、#fooチャンネルのオペレーターでないnick1が、次のように実行した場合です。
TOPIC #foo 新しいトピック

todo topic
*/
void CmdManager::topic(Client& sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 1, 2)) return;
	std::string channel_name = cmd._params[0];
	if (!channelManager.require_exist_channel(sender, channel_name)) return;
	Channel &channel = channelManager.get_channel(channel_name);
	if (cmd.has_trailing())
		channel.set_topic(sender, cmd._trailing);
	else 
		channel.show_topic(sender);
}