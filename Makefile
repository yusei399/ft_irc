NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
SRCS = src/Message.cpp
       src/CheckRegister.cpp
       src/Channel/cmd/KICK.cpp
       src/Channel/cmd/NOTICE.cpp 
       src/Channel/cmd/TOPIC.cpp 
       src/Channel/cmd/PART.cpp
       src/Channel/cmd/NAMES_ALL.cpp
       src/Channel/cmd/NAMES.cpp 
       src/Channel/cmd/INVITE.cpp 
       src/Channel/cmd/QUIT.cpp 
       src/Channel/cmd/JOIN.cpp 
       src/Channel/cmd/PRIVMSG.cpp 
       src/Channel/cmd/MODE.cpp
       src/Channel/Channel.cpp 
       src/Channel/ChannelManager.cpp 
       src/FtCfunc.cpp
       src/Command/cmd/KICK.cpp 
       src/Command/cmd/TOPIC.cpp 
       src/Command/cmd/PASS.cpp 
       src/Command/cmd/PART.cpp
       src/Command/cmd/CAP.cpp 
       src/Command/cmd/PING.cpp
       src/Command/cmd/NAMES.cpp 
       src/Command/cmd/INVITE.cpp 
       src/Command/cmd/WHO.cpp
       src/Command/cmd/USER.cpp 
       src/Command/cmd/QUIT.cpp 
       src/Command/cmd/JOIN.cpp
       src/Command/cmd/NICK.cpp
       src/Command/cmd/MSG.cpp
       src/Command/cmd/MODE.cpp
       src/Command/CmdBuffer.cpp 
       src/Command/CmdManager.cpp
       src/Command/Command.cpp
       src/StringExtend.cpp
       src/Client/Client.cpp
       src/Client/ClientManager.cpp 
       src/main.cpp
       src/Server.cpp
OBJDIR = obj
OBJS = $(subst $(SRCDIR), $(OBJDIR), $(SRCS:%.cpp=%.o))

INC = include

RM = rm -rf

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -I$(INC) $(CXXFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) -I$(INC) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(RM) $(OBJDIR)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

