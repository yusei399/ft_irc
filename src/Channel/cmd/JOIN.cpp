#include "Channel.hpp"
#include "ChannelManager.hpp"

static bool require_invited_conditions(Client &client, Channel& channel)
{
    if (channel.is_invited_mode() && !channel.is_invited(client))
	{
        reply(client, ERR_INVITEONLYCHAN(client, channel));
		return false;
	}
	return true;
}

//存在しないチャンネルに対してjoinを行った場合はこの関数ではなくコンストラクタで処理する
void Channel::join(const Command&cmd, Client& sender, const std::string & pass)
{
    if (!require_invited_conditions(sender, *this)) return;
    //すでに属しているチャンネルにjoinを行った場合,本家はエラーをおこさないらしいので、とりあえず何もしないことにする。
    if (is_member(sender))
        return;
    if (!require_limit_safe(sender)) 
        return;
    if (!correct_pass(pass))
    {
        reply(sender, ERR_BADCHANNELKEY(sender, (*this)));
        return;
    }
    members.insert(sender);
    reply_cmd_all(sender, cmd);
    reply(sender,get_rpl_topic_msg(sender));
    names(sender);
}

void ChannelManager::join(const Command& cmd, Client &client, const std::vector<std::string> &ch_names, const std::vector<std::string> &ch_pass)
{
	for(size_t i = 0; i < ch_names.size(); i++)
	{
		if (!require_valid_channel_name(client, ch_names[i]))
			continue;
		if (exist_channel(ch_names[i]))
			get_channel(ch_names[i]).join(cmd, client, ch_pass[i]);
		else
		    channels.insert(Channel(cmd, ch_names[i], client, ch_pass[i]));
	}
}