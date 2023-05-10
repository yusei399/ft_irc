#include "CmdManager.hpp"
#include "CommandList.hpp"
#include "Client.hpp"
#include "ChannelManager.hpp"
#include "CheckRegister.hpp"


static bool require_enough_params(Client &client, const Command& cmd)
{
	if (cmd._params.size() == 0 || cmd._params.size() > 2)
	{
		send_errmsg(client, 461, cmd.get_original_str() + " :Not enough parameters");
		return false;
	}
	return true;
}

static std::vector<std::string> parse_ch_names(const Command& cmd)
{
	return split(cmd._params[0], ",");;
}

//指定されたチャンネルよりもパスワードの数が多くてもエラーは出さない(本家仕様)
//チャンネルの数に対して足りないパスワードには空文字列を入れる
static std::vector<std::string> parse_ch_pass(const Command& cmd, const std::vector<std::string> &ch_names)
{
	std::vector<std::string> ch_pwds = split(cmd._params[1], ",");
	if (ch_pwds.size() < ch_names.size())
		ch_pwds.resize(ch_names.size());
	return ch_pwds;
}

//JOIN #ch1[,#ch2] [pass_ch1,pass_ch2]
//存在しないチャンネルを指定した場合無視する(本家通り)
//複数のチャンネルを指定した際、その中で存在するチャンネルにはjoinできる
void CmdManager::join(Client &client, const Command& cmd)
{
	if (!require_authed(client)) return;
	if (!require_nick_user(client)) return;
	if (!require_enough_params(client, cmd)) return;
	std::vector<std::string> ch_names = parse_ch_names(cmd);
	std::vector<std::string> ch_pass = parse_ch_pass(cmd, ch_names);
	channelManager.join(client, ch_names, ch_pass);
}