NAME = minishell

CC = gcc

LIBFT_DIR =	./libft/
LIBFT = 	$(addprefix $(LIBFT_DIR), libft.a)

CFLAGS = 	-Wall -Wextra -Werror \
			-Iinc \
			-I$(LIBFT_DIR) \
			-I/opt/homebrew/Cellar/readline/8.1.1/include

LFLAGS =	-L. $(LIBFT) \
			-L/opt/homebrew/Cellar/readline/8.1.1/lib \
			-lreadline

SRC =	src/main.c \
		src/signal_handling/signal_handling.c \
		src/lexer/lex_new_token.c \
		src/lexer/lex_new.c \
		src/lexer/lex_next_token.c \
		src/lexer/lex_peek_char.c \
		src/lexer/lex_read_char.c \
		src/lexer/lex_valid_syntax.c
		

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) $(SRC) -o $(NAME)

$(LIBFT):
	@make -C libft
