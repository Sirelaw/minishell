#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>

# include <signal_handling.h>
# include <lexer.h>

typedef struct s_shell_env
{
	char	**envp;
	int		last_exit_code;
}				t_shell_env;

#endif
