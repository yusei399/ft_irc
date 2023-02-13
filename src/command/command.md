# コマンド
## コマンド一覧
- CAP
	- CAP (Client Capability Negotiation)
	- クライアントとサーバー間での能力の認識、要求、および応答を行うために使用される。
	[コマンド]
	- CAP LS: サーバーが提供する能力のリストを要求します。
    - CAP REQ : 要求する能力を指定します。
    - CAP ACK: 要求された能力が承認されました。
    - CAP NAK: 要求された能力が拒否されました。
- PASS
- NICK
	- /NICK nickname: あなたのニックネームを変更します。
- USER
- JOIN
	- /JOIN #channel: 指定されたチャンネルに参加します。
- TOPIC
	- /TOPIC #channel topic: 指定されたチャンネルのトピックを変更します。
- PING
- NAMES
- MODE
- PRIVMSG
- NOTICE
- QUIT
	- /QUIT [message]: サーバーから切断します。オプションのメッセージがある場合は、それが切断メッセージとして送信されます。
- KICK
- INVITE
	- /INVITE nickname #channel: 指定されたニックネームを指定されたチャンネルに招待します。
- PART
	- /PART #channel: 指定されたチャンネルから退出します。
