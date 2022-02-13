/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:20 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/13 18:11:05 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

t_shell_env	g_shell_env;

static char	**dup_envp(char **envp)
{
	char	**new;
	size_t	i;

	i = 0;
	while (envp[i])
		++i;
	new = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		++i;
	}
	return (new);
}

int	loop(t_shell_env *shell_env)
{
	char	*line;
	t_lexer	j;

	(void)shell_env;
	sig_handle_interactive();
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			;
		if (ft_strlen(line) > 0)
			add_history(line);
		if (lex_valid_syntax(line))
		{
			j = lex_new(line);
			sig_handle_exec();
			pipex(&j);
			sig_handle_interactive();
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_shell_env.envp = dup_envp(envp);
	g_shell_env.last_exit_code = 0;
	(void)argc;
	(void)argv;
	loop(&g_shell_env);
	return (EXIT_SUCCESS);
}
