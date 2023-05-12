#include "CmdManager.hpp"
#include "Mode.hpp"

void CmdManager::mode_i(Client&sender, const Command&cmd)
{
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_I)
        channel.send_mode_state_i(sender);
	else if (flag == MODE_I_ADD)
        channel.mode_i(sender, true);
    else if (flag == MODE_I_REM)
        channel.mode_i(sender,  false);
	else
		throw std::logic_error("");
}

void CmdManager::mode_o(Client&sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 3, 6))return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	std::string target_nick = cmd._params[2];
	if (!clientManager.require_exist_nick(sender, target_nick) )
		return;
	Client &target = clientManager.get_client_by_nick(target_nick);
	if (flag == MODE_O_ADD)
       	channel.mode_o(sender, true, target);
	else if(flag == MODE_O_REM)
       	channel.mode_o(sender, false, target);
	else
		throw std::logic_error("");
}

/*
チャンネルのトピックとは、チャンネルの内容や目的を表す短い文です。チャンネルに参加すると、トピックが表示されます。また、チャンネルのリストを見るときにも、トピックが表示されます。トピックは、チャンネルのオペレーターが変更できます。

TOPICコマンドは、チャンネルのトピックを設定したり、確認したりするために使います。TOPICコマンドのパラメーターの渡し方は、次のようになります。

TOPIC <channel> [<topic>]

<channel>: トピックを設定したり、確認したりするチャンネルの名前です。 <topic>: トピックを設定する場合に指定します。省略すると、現在のトピックを確認できます。

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
void CmdManager::mode(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 2, 6))	return;
	if (is_mode_i(cmd))
		mode_i(sender, cmd);
    else if (is_mode_o(cmd))
		mode_o(sender, cmd);
	else
        send_errmsg(sender, 472, get_flag(cmd)+ " :is unknown mode char to me");
}
