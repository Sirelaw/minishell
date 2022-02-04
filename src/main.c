/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:20 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/04 19:10:19 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

char	**create_cmd_chain(char **cmd_chain, char *literal)
{
	char	**temp;
	int		i;

	if (cmd_chain == NULL)
	{
		temp = malloc(2 * sizeof(char *));
		temp[0] = literal;
		temp[1] = NULL;
		return (temp);
	}
	i = 0;
	while (cmd_chain[i])
		i++;
	temp = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (cmd_chain[i++])
		temp[i - 1] = cmd_chain[i - 1];
	temp[i - 1] = literal;
	temp[i] = NULL;
	free(cmd_chain);
	return (temp);
}

int	loop(t_shell_env *shell_env)
{
	char	*line;
	char	**cmd_chain;

	(void)shell_env;
	cmd_chain = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			;
		if (ft_strlen(line) > 0)
			add_history(line);
		// FOR TESTING ->
		if (lex_valid_syntax(line))
		{
			t_lexer	l = lex_new(line);
			for (t_token t = lex_next_token(&l); t.type != END; t = lex_next_token(&l))
			{
				//cmd_chain = create_cmd_chain(cmd_chain, t.literal);
				 printf("%s	%d\n", t.literal, t.type);
				// free(t.literal);
			}
			pipex(cmd_chain, shell_env->envp);
			//free all t.literal after
		}
		// <- FOR TESTING
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	shell_env;

	shell_env.envp = envp;
	shell_env.last_exit_code = 0;
	handle_signals(); ////////////commented out for testing
	(void)argc;
	(void)argv;
	loop(&shell_env);
	return (EXIT_SUCCESS);
}
