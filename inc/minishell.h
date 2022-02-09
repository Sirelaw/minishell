/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:38 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/09 12:52:55 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <built_in.h>

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
int		pipex(t_lexer *l, t_shell_env *shell_env);

/*
 *	Expands all environment variables in *str
 *	given they are not enclosed in single quotes
*/
char	*expand_str(char **envp, char **str);

#endif
