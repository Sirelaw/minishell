/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 00:55:13 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/23 02:06:30 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i++])
		free(arr[i - 1]);
	if (arr)
		free(arr);
}

static void	free_cmd(t_cmd *cmd)
{
	free_arr(cmd->infile);
	free_arr(cmd->outfile);
	free_arr(cmd->outfile_type);
	free_arr(cmd->cmds);
	free(cmd->cmdpath);
	free(cmd);
}

void	free_all(t_input *input)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (input)
	{
		cmd = input->cmd_chain;
		while (cmd)
		{
			temp = cmd->next;
			free_cmd(cmd);
			cmd = temp;
		}
		free_arr(input->path);
		free(input);
	}
}
