/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oipadeol <oipadeol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:21:50 by oipadeol          #+#    #+#             */
/*   Updated: 2022/02/05 15:14:16 by oipadeol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_cmd	*new_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->cmds = NULL;
	cmd->cmdpath = NULL;
	cmd->delimiter = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->re_in = FALSE;
	cmd->re_out = FALSE;
	cmd->append_out = FALSE;
	cmd->append_in = FALSE;
	cmd->next = NULL;
	return (cmd);
}

void	t_cmd_add_back(t_cmd **head, t_cmd *latest)
{
	t_cmd *temp;

	temp = *head;
	if (temp == NULL)
		*head = latest;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = latest;
	}
}
