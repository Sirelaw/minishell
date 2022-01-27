CC = gcc
CFLAGS = -Wall -Werror -Wextra -c

NAME = libft.a

all: $(NAME)

$(NAME): *.c
	@$(CC) $(CFLAGS) *.c
	@ar cr $@ *.o
	@rm -f *.o

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
