NAME = ircserv

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRCDIR = src
SRCS = $(shell find $(SRCDIR) -name "*.cpp" -type f)

OBJDIR = obj
OBJS = $(subst $(SRCDIR), ./$(OBJDIR), $(SRCS:%.cpp=%.o))

DEPS    =    $(SRCS:%.cpp=%.d)

INC = include

RM = rm -rf

all: $(NAME)

$(OBJDIR)/%.o:$(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -I$(INC) -o $@ -c $<
	@echo "$< =========> $(GRN) $@ $(RES)"

$(NAME):$(OBJS)
	@$(CXX) -I$(INC) -o $(NAME) $(OBJS)
	@echo "$(CYN)\n=====link=====$(RES)"
	@echo "$(YEL)Objects$(RES): $(OBJS)\n"
	@echo "$(YEL)Flags$(RES): $(CXXFLAGS)\n"
	@echo "     $(MGN)--->$(RES) $(GRN)$(NAME)$(RES)"
	@echo "$(CYN)==============$(RES)"

clean:
	$(RM) $(OBJS)
	$(RM) $(NAME)
	@$(RM) $(OBJDIR)

fclean:clean

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)

RED = \033[31m
GRN = \033[32m
YEL = \033[33m
BLU = \033[34m
MGN = \033[35m
CYN = \033[36m
RES = \033[m
