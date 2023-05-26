NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
SRCS = $(SRCDIR)/Message.cpp \
       $(SRCDIR)/CheckRegister.cpp \
       $(SRCDIR)/Channel/cmd/KICK.cpp \
       $(SRCDIR)/Channel/cmd/NOTICE.cpp \
       $(SRCDIR)/Channel/cmd/TOPIC.cpp \
       $(SRCDIR)/Channel/cmd/PART.cpp \
       $(SRCDIR)/Channel/cmd/NAMES_ALL.cpp \
       $(SRCDIR)/Channel/cmd/NAMES.cpp \
       $(SRCDIR)/Channel/cmd/INVITE.cpp \
       $(SRCDIR)/Channel/cmd/QUIT.cpp \
       $(SRCDIR)/Channel/cmd/JOIN.cpp \
       $(SRCDIR)/Channel/cmd/PRIVMSG.cpp \
       $(SRCDIR)/Channel/cmd/MODE.cpp \
       $(SRCDIR)/Channel/Channel.cpp \
       $(SRCDIR)/Channel/ChannelManager.cpp \
       $(SRCDIR)/FtCfunc.cpp \
       $(SRCDIR)/Command/cmd/KICK.cpp \
       $(SRCDIR)/Command/cmd/TOPIC.cpp \
       $(SRCDIR)/Command/cmd/PASS.cpp \
       $(SRCDIR)/Command/cmd/PART.cpp \
       $(SRCDIR)/Command/cmd/CAP.cpp \
       $(SRCDIR)/Command/cmd/PING.cpp \
       $(SRCDIR)/Command/cmd/NAMES.cpp \
       $(SRCDIR)/Command/cmd/INVITE.cpp \
       $(SRCDIR)/Command/cmd/WHO.cpp \
       $(SRCDIR)/Command/cmd/USER.cpp \
       $(SRCDIR)/Command/cmd/QUIT.cpp \
       $(SRCDIR)/Command/cmd/JOIN.cpp \
       $(SRCDIR)/Command/cmd/NICK.cpp \
       $(SRCDIR)/Command/cmd/MSG.cpp \
       $(SRCDIR)/Command/cmd/MODE.cpp \
       $(SRCDIR)/Command/CmdBuffer.cpp \
       $(SRCDIR)/Command/CmdManager.cpp \
       $(SRCDIR)/Command/Command.cpp \
       $(SRCDIR)/StringExtend.cpp \
       $(SRCDIR)/Client/Client.cpp \
       $(SRCDIR)/Client/ClientManager.cpp \
       $(SRCDIR)/main.cpp \
       $(SRCDIR)/Server.cpp

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
	$(RM) $(OBJDIR)

fclean:
	$(RM) $(OBJS)
	$(RM) $(OBJDIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
