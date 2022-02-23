/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 01:03:17 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/23 01:15:24 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	open_all_infile(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->infile && cmd->infile[i++])
	{
		if (cmd->fd[0] != -1)
			close(cmd->fd[0]);
		cmd->fd[0] = open(cmd->infile[i - 1], O_RDONLY);
		if (cmd->fd[0] < 0)
			perror(cmd->infile[i - 1]);
		if (cmd->fd[0] < 0)
			return (1);
	}
	return (0);
}

static int	open_all_outfile(t_cmd *cmd)
{
	int			i;
	const int	m = O_WRONLY | O_CREAT;

	i = 0;
	while (cmd->outfile && cmd->outfile[i++])
	{
		if (cmd->fd[1] != -1)
			close(cmd->fd[1]);
		if (*(cmd->outfile_type[i - 1]) == 'A')
			cmd->fd[1] = open(cmd->outfile[i - 1], m | O_APPEND, 0666);
		else
			cmd->fd[1] = open(cmd->outfile[i - 1], m | O_TRUNC, 0666);
		if (cmd->fd[1] < 0)
			perror(cmd->outfile[i - 1]);
		if (cmd->fd[1] < 0)
			return (1);
	}
	return (0);
}

int	open_infile_outfile(t_cmd *cmd)
{
	if (open_all_infile(cmd))
		return (1);
	if (open_all_outfile(cmd))
		return (1);
	return (0);
}
