# Name of the program
NAME = minishell

# Color codes

RESET	= \033[0m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m

# Compiling flags
# FLAGS = -Wall -Wextra -Werror
FLAGS = 
LFLAGS = -L$$HOME/.brew/opt/readline/lib -lreadline
CPFLAGS = -I$$HOME/.brew/opt/readline/include

# Folders
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
LIBFT_DIR = ./libft/

# Source files and object files
SRC_FILES = main.c signal_handling/signal_handling.c lexer/lex_new_token.c \
		lexer/lex_new.c lexer/lex_next_token.c lexer/lex_peek_char.c \
		lexer/lex_read_char.c lexer/lex_valid_syntax.c env_expand/env_expand.c\
		built_in/cd.c built_in/echo.c built_in/env.c built_in/export.c \
		built_in/pwd.c built_in/unset.c pipe/pipex.c pipe/check_cmd.c\
		pipe/t_cmd_utils.c pipe/cmd_utils.c pipe/exec_cmd.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft 

# all rule
all: obj $(LIBFT) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)lexer
	@mkdir -p $(OBJ_DIR)signal_handling
	@mkdir -p $(OBJ_DIR)env_expand
	@mkdir -p $(OBJ_DIR)built_in
	@mkdir -p $(OBJ_DIR)pipe

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) $(CPFLAGS) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "$(YELLOW)\n      -> Building $(NAME) ...$(RESET)"
	@gcc $(OBJ) $(LFLAGS) $(LNK) -lm -o $(NAME)
	@echo "$(GREEN)***   Project $(NAME) successfully compiled   ***\n$(RESET)"

# clean rule
clean:
	@echo "$(BLUE)***   Deleting all objects from $(NAME)   ...   ***$(RESET)"
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo

# fclean rule
fclean: clean
	@echo "$(BLUE)***   Deleting executable file from $(NAME)   ...   ***$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re
