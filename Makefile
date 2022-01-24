NAME =	philo
CC = 	clang -Wall -Werror -Wextra
AR =	ar rcs
RM = 	rm -rf

FLAGS =	-pthread
FLAGS += -O2
#FLAGS += -g
#FLAGS += -fsanitize=address
#FLAGS += -fsanitize=thread

# **************************************************************************** #
#	MAKEFILE	#

MAKEFLAGS += --silent

SHELL := bash

B =		$(shell tput bold)
BLA =	$(shell tput setaf 0)
RED =	$(shell tput setaf 1)
GRE =	$(shell tput setaf 2)
YEL =	$(shell tput setaf 3)
BLU =	$(shell tput setaf 4)
MAG =	$(shell tput setaf 5)
CYA =	$(shell tput setaf 6)
WHI =	$(shell tput setaf 7)
D =		$(shell tput sgr0)
BEL =	$(shell tput bel)
CLR =	$(shell tput el 1)

# **************************************************************************** #
#	 LIB	#

# LBPATH =	./libft/
# LBNAME =	$(LBPATH)libft.a
# LBINC =		-I$(LBPATH)
# LBM =		libm

# **************************************************************************** #
#	SRCS	#

SRCSPATH =	./sources/
OBJSPATH =	./objs/
INC =		./includes/

#SRCSNAME =	main.c \
			ft_arg.c \
			init.c \
			ft_run.c \
			utils.c

#SRCS = $(addprefix $(SRCSPATH), $(SRCSNAME))
SRCS = $(wildcard $(SRCSPATH)*.c) $(wildcard $(SRCSPATH)**/*.c)
SRCSNAME =	$(subst $(SRCSPATH), , $(SRCS))

OBJSNAME = $(SRCSNAME:.c=.o)
OBJS = $(addprefix $(OBJSPATH), $(OBJSNAME))

# *************************************************************************** #

define	progress_bar
	@i=0; \
	while [[ $$i -le $(words $(SRCS)) ]]; do \
		printf " "; \
		((i = i + 1)); \
	done; \
	printf "$(B)]\r[$(GRE)";
endef

# *************************************************************************** #
#	RULES	#

all:		launch $(NAME)
	@printf "\n$(B)$(MAG)$(NAME) compiled$(D)\n"

launch:
	$(call progress_bar)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJSPATH)%.o: $(SRCSPATH)%.c
	@mkdir -p $(dir $@) # 2> /dev/null || true
	$(CC) $(FLAGS) -I$(INC) -c $< -o $@
	@printf "█"

clean:
	@$(RM) $(OBJSPATH)
	@echo "$(B)Cleared$(D)"


fclean:		clean
	@$(RM) $(OBJSPATH)
	@$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re launch #lib

# **************************************************************************** #