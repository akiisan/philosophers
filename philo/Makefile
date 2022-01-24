NAME	=		philo
CC		=		gcc -pthread -g3 -fsanitize=address #|| -fsanitize=thread
GREEN	=		'\033[0;32m'

SRC		=	philo.c philo2.c routine.c utils.c utils2.c utils3.c display.c check.c check2.c
		
OBJS=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) -I . -Wall -Werror -Wextra -o $(NAME) -g
	@echo ${GREEN}FINI !

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PONY: all clean fclean re 