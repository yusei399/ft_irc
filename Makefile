NAME = ircserv

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
SRCS = $(shell find $(SRCDIR) -name "*.cpp" -type f)

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
