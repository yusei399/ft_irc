#include "CmdManager.hpp"
#include "Mode.hpp"

void CmdManager::mode_i(Client&sender, const Command&cmd)
{
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_I)
        channel.mode_i_state(sender);
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

void CmdManager::mode_t(Client&sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_T)
		channel.mode_t_state(sender);
	else if (flag == MODE_T_ADD)
		channel.mode_t(sender, true);
	else if (flag == MODE_T_REM)
		channel.mode_t(sender, false);
	else
		throw std::logic_error("");
}

/*
IRCのMODEコマンドは、チャンネルやユーザーのモードを変更または表示するために使用されます1。kコマンドは、チャンネルにパスワードを設定するためのモードです2。

MODE #channel_name -kは、チャンネルからパスワードを削除するコマンドです。このコマンドを実行するには、チャンネルのオペレーター権限が必要です2。例えば、MODE #test -kと打ったときのメッセージは、

:nick MODE #test -k

となります。これは、自分がチャンネル#testからパスワードを削除したことを示します。

MODE #channel_name +k <password>は、チャンネルにパスワードを設定するコマンドです。このコマンドを実行するには、チャンネルのオペレーター権限が必要です2。例えば、MODE #test +k secretと打ったときのメッセージは、

:nick MODE #test +k secret

となります。これは、自分がチャンネル#testにパスワードsecretを設定したことを示します。

MODE #channel_name kは、チャンネルのパスワードを表示するコマンドです。このコマンドを実行するには、チャンネルに参加している必要があります2。例えば、MODE #test kと打ったときのメッセージは、

:server 324 nick #test +k secret

となります。これは、サーバーがチャンネル#testのパスワードがsecretであることを示します。

発生しうるエラーについて番号付きでその起きる例を交えて解説してください

以下は、発生しうるエラーとその起きる例です。

ERR_NEEDMOREPARAMS: パラメーターが足りない場合に発生します。例えば、MODE #test +kと打った場合に発生します。 :server 461 nick MODE :Not enough parameters

ERR_NOSUCHCHANNEL: 存在しないチャンネル名を指定した場合に発生します。例えば、MODE #foo kと打った場合に発生します。 :server 403 nick #foo :No such channel

ERR_NOTONCHANNEL: チャンネルに参加していない場合に発生します。例えば、MODE #test kと打った場合に発生します。 :server 442 nick #test :You’re not on that channel

ERR_CHANOPRIVSNEEDED: チャンネルのオペレーター権限がない場合に発生します。例えば、MODE #test +k secretと打った場合に発生します。 :server 482 nick #test :You’re not channel operator


MODE #test -kというコマンドを入力した際には、コマンドを打った本人にだけメッセージが返されます。メッセージは、

:nick MODE #test -k

となります。これは、自分がチャンネル#testからパスワードを削除したことを示します。

MODE #test +k secretというコマンドを入力した際には、コマンドを打った本人とチャンネル#testにいる全員にメッセージが送られます。メッセージは、

:nick MODE #test +k secret

となります。これは、自分がチャンネル#testにパスワードsecretを設定したことを示します。

MODE #test kというコマンドを入力した際には、コマンドを打った本人にだけメッセージが返されます。メッセージは、

:server 324 nick #test +k secret

となります。これは、サーバーがチャンネル#testのパスワードがsecretであることを示します
*/

void CmdManager::mode_k(Client&sender, const Command&cmd)
{
	if (!require_enough_params(sender, cmd, 2, 6))return;
	if (!channelManager.require_exist_channel(sender, cmd._params[0])) return;
	Channel &channel = channelManager.get_channel(cmd._params[0]);
	std::string flag = get_flag(cmd);
	if (flag == MODE_K)
		channel.mode_k_state(sender);
	else if (flag == MODE_K_ADD)
		channel.mode_k_rem(sender, true);
	else if (flag == MODE_K_REM)
	{
		
		channel.mode_k_rem(sender, false);
	}
	else
		throw std::logic_error("");
}

void CmdManager::mode(Client &sender, const Command& cmd)
{
	if (!require_authed(sender)) return;
	if (!require_nick_user(sender)) return;
	if (!require_enough_params(sender, cmd, 2, 6))	return;
	if (is_mode_i(cmd))
		mode_i(sender, cmd);
    else if (is_mode_o(cmd))
		mode_o(sender, cmd);
	else if (is_mode_t(cmd))
		mode_t(sender, cmd);
	else if (is_mode_k(cmd))
		mode_k(sender, cmd);
	else
        send_numeric_msg(sender, 472, get_flag(cmd)+ " :is unknown mode char to me");
}
