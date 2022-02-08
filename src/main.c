/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachmull <sachmull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:17:20 by sachmull          #+#    #+#             */
/*   Updated: 2022/02/08 20:02:28 by sachmull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minishell.h>

int	loop(t_shell_env *shell_env)
{
	char	*line;
	t_lexer	j;

	(void)shell_env;
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
			pipex(&j, shell_env->envp);
			sig_handle_interactive();
		}
		
		// FOR TESTING ->
		// if (lex_valid_syntax(line))
		// {
		// 	t_lexer	l = lex_new(line);
		// 	for (t_token t = lex_next_token(&l); t.type != END; t = lex_next_token(&l))
		// 	{
		// 		printf("%s	%d\n", t.literal, t.type);
		// 		free(t.literal);
		// 	}
		// }
		// else
		// 	printf("Invalid syntax\n");
		// <- FOR TESTING
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_env	shell_env;

	shell_env.envp = envp;
	shell_env.last_exit_code = 0;
	sig_handle_interactive();
	(void)argc;
	(void)argv;
	loop(&shell_env);
	return (EXIT_SUCCESS);
}
