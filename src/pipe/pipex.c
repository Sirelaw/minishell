/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:10 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/28 14:05:50 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipex(t_lexer *l)
{
	t_input	*input;
	int		exit_code;

	errno = 0;
	input = malloc(sizeof(t_input));
	if (!input || do_init(input))
	{
		free_all(input);
		return (g_shell_env.last_exit_code);
	}
	input->cmd_chain = build_chain(l, input);
	if (input->cmd_chain->cmds)
	{
		pipe(input->fd[0]);
		pipe(input->fd[1]);
		exit_code = exec_cmds(input, input->cmd_chain);
		if (WIFEXITED(exit_code) && !g_shell_env.last_exit_code)
			g_shell_env.last_exit_code = WEXITSTATUS(exit_code);
	}
	free_all(input);
	return (g_shell_env.last_exit_code);
}
