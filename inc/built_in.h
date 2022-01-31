#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <minishell.h>

int	cd(char **argv, char **envp);
int	echo(char **argv);
int	env(char **envp);
int	export(char **argv, char ***envp);
int	pwd();
int	unset(char **argv, char ***envp);

#endif
