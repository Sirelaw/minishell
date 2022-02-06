/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:11:10 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/06 22:58:04 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pipex(t_lexer *l, char **envp)
{
	t_input	*input;
	int		i;

	errno = 0;
	i = 0;
	input = malloc(sizeof(t_input));
	if (do_init(envp, input))
		exit (EXIT_FAILURE);
	input->cmd_chain = build_chain(l, input);
	if (input->cmd_chain->cmds)
	{
		pipe(input->fd[0]);
		pipe(input->fd[1]);
		exec_cmds(input, input->cmd_chain);
	}
	// Testing block
	// if (input->cmd_chain->outfile)
	// 	while (input->cmd_chain->outfile[i])
	// 		printf("%s\n", input->cmd_chain->outfile[i++]);
	//--------------
	// free_all_allocs()
	return (0);
}
