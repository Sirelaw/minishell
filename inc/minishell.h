#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <libft.h>

# include <signal_handling.h>
# include <lexer.h>
# include <pipex.h>

typedef struct s_shell_env
{
	char	**envp;
	int		last_exit_code;
}				t_shell_env;

/*
var is passed as the string "$VAR" into the function along with the envp
pointer.
*/
char	*env_expand(char **envp, char *var);
int		pipex(char **cmd_chain, char **envp);

#endif
